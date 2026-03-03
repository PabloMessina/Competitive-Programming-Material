#!/usr/bin/env python3
from __future__ import annotations # for type hints
from dataclasses import dataclass
import os
from pathlib import Path
import subprocess
import sys
import time
import re
import yaml
from argparse import ArgumentParser
from typing import Any

EXT_WHITELIST = [".cpp", ".c", ".typ", ".txt"]
NEWLINE = "\n"

base_path = Path(__file__).parent
conf: "Conf"
yaml_config: dict

def section_name(raw: str) -> str | None:
    if raw.startswith("."):
        return None
    return " ".join(w.capitalize() for w in raw.split())

def file_name(name: str) -> str | None:
    for ext in EXT_WHITELIST:
        if name.endswith(ext):
            name = name.removesuffix(ext)
            name = re.split(r"[-_\s]+", name)
            return " ".join(w.lower() for w in name)
    return None

def file_contents(filename: str, raw: str) -> str:
    if filename.endswith(".typ"):
        return Verbatim("[\n" + raw.strip() + "\n]")

    extension = ""
    if "." in filename:
        extension = filename.split(".")[-1]
    return Verbatim("```"+extension+"\n"+raw.strip()+"\n```")

class Verbatim(str):
    pass

def serialize(val: Any) -> str:
    if isinstance(val, Verbatim):
        return val
    if isinstance(val, bool):
        return "true" if val else "false"
    if isinstance(val, float) or isinstance(val, int):
        return str(val)
    if isinstance(val, str):
        return '"' + val.replace("\\", "\\\\").replace("\"", "\\\"") + '"'
    if isinstance(val, list) or isinstance(val, tuple):
        return "(" + "".join(serialize(subval) + "," for subval in val) + ")"
    if not isinstance(val, dict):
        val = {attrname: getattr(val, attrname) for attrname in dir(val) if not attrname.startswith("_")}
    if not val:
        return "(:)"
    for k in val:
        if not isinstance(k, str):
            raise RuntimeError("dictionary key must be a string")
    return "("+",".join(serialize(k) + ":" + serialize(v) for k, v in val.items())+")"

def compose(sections: list[tuple[str, list[tuple[str, str]]]]) -> str:
    args = {
        "conf": conf,
        "content": sections,
    }
    # Note the updated import path here
    return f"""
#import ".typst/template.typ": compose
#compose({serialize(args)})
    """

def ingest() -> list[tuple[str, list[tuple[str, str]]]]:
    sections = []
    included_sections = yaml_config.get("sections", [])
    exclude_dirs = set(yaml_config.get("exclude_dirs", []))
    exclude_files = set(yaml_config.get("exclude_files", []))
    file_names_to_sort_first: list[str] = yaml_config.get("file_names_to_sort_first", [])

    def file_name_to_sort_key(filename: str) -> tuple[int, str]:
        try:
            return (file_names_to_sort_first.index(filename), filename)
        except ValueError:
            return (float('inf'), filename)

    for dirname in included_sections:
        dir_path = base_path.joinpath(dirname)
        if not dir_path.is_dir() or dirname in exclude_dirs:
            continue

        secname = section_name(dirname)
        if secname is not None:
            sec = []
            for root, dirs, files in os.walk(dir_path):
                dirs[:] = [d for d in dirs if d not in exclude_dirs and not d.startswith('.')]

                for filename in files:
                    if filename in exclude_files:
                        continue

                    fname = file_name(filename)
                    if fname is not None:
                        filepath = Path(root).joinpath(filename)
                        try:
                            txt = filepath.read_text(encoding="utf-8")
                        except UnicodeDecodeError:
                            print(f"Skipping {filepath} (not valid UTF-8)", file=sys.stderr)
                            continue

                        sub_path = Path(root).relative_to(dir_path)
                        display_name = fname
                        if str(sub_path) != ".":
                            display_name = f"{sub_path} / {fname}"

                        sec.append((display_name, file_contents(filename, txt)))
            
            if sec:
                sec.sort(key=lambda x: file_name_to_sort_key(x[0]))
                sections.append((secname, sec))
    return sections

def compile(src: str):
    if conf.print_source:
        print("printing source code instead of compiling...", file=sys.stderr)
        print(src)
    else:
        out_path = base_path.joinpath(conf.out)
        try:
            subprocess.run(
                ["typst", "compile", "--root", base_path, "--format", "pdf", "-", out_path],
                input=src.encode("utf-8"),
                check=True
            )
            print(f"wrote pdf to {conf.out}", file=sys.stderr)
        except FileNotFoundError:
            raise RuntimeError("Typst is not installed. Please run 'brew install typst'.")
        except subprocess.CalledProcessError as e:
            raise RuntimeError(f"Typst compilation failed: {e}")

@dataclass
class Conf:
    out: str
    university: str
    team: str
    print_source: bool
    font_size: Verbatim
    column_count: int
    column_gutter: Verbatim
    margin: Verbatim
    paper: str
    portrait: bool
    theme: str

    @staticmethod
    def load(data: dict) -> "Conf":
        p = ArgumentParser()
        p.add_argument("--print-source", action="store_true")
        parsed = p.parse_args(sys.argv[1:])

        return Conf(
            out=data.get("out", "notebook.pdf"),
            university=data.get("university", "University Name"),
            team=data.get("team", "Team Name"),
            print_source=parsed.print_source,
            font_size=Verbatim(data.get("font_size", "6.984pt")),
            column_count=int(data.get("column_count", 3)),
            column_gutter=Verbatim(data.get("column_gutter", "5mm")),
            margin=Verbatim(data.get("margin", "10mm")),
            paper=data.get("paper", "a4"),
            portrait=bool(data.get("portrait", False)),
            theme=data.get("theme", "Custom")
        )

def main():
    global conf, yaml_config
    start = time.monotonic()

    config_path = base_path.joinpath("config.yaml")
    if not config_path.is_file():
        print("Error: config.yaml not found in the repository root.", file=sys.stderr)
        sys.exit(1)

    with open(config_path, 'r') as f:
        yaml_config = yaml.safe_load(f) or {}

    conf = Conf.load(yaml_config)

    print("processing input files...", file=sys.stderr)
    sections = ingest()
    src = compose(sections)

    print("compiling to pdf...", file=sys.stderr)
    compile(src)
    
    print(f"done in {time.monotonic() - start:.2f}s", file=sys.stderr)

if __name__ == "__main__":
    main()