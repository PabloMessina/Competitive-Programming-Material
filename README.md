# Competitive Programming Material

Templates, notes and solved problems for competitive programming (ICPC-style contests).
The templates are compiled into a printable team notebook, `notebook.pdf`.

## Generating `notebook.pdf`

The notebook is built by `make.py`, which collects the source files listed in `config.yaml`
and compiles them into a PDF with [Typst](https://typst.app/).

### Requirements

- Python 3.9+ with [PyYAML](https://pypi.org/project/PyYAML/)
- The Typst CLI

```bash
pip3 install pyyaml

# Typst (pick one)
brew install typst            # macOS / Linux with Homebrew
cargo install --locked typst-cli
# or download a binary from https://github.com/typst/typst/releases
```

The notebook uses New Computer Modern and DejaVu Sans Mono, both of which come bundled with Typst, so you don't need to install any fonts.

### Build

From the repository root:

```bash
python3 make.py                 # writes notebook.pdf
python3 make.py --print-source  # prints the generated Typst source instead (for debugging)
```

### How it works

1. `make.py` reads `config.yaml`.
2. Each folder listed under `sections` becomes a section of the notebook, in the order listed.
   Folders are scanned recursively.
3. Only files with these extensions are included: `.cpp`, `.c`, `.typ`, `.txt`.
   - Code files are inserted as syntax-highlighted code blocks.
   - `.typ` files are inserted as Typst markup, so they can contain formatted text and math.
   - Other files (`.md`, `.py`, PDFs, ...) are ignored.
4. Folders in `exclude_dirs`, folders starting with `.`, and files in `exclude_files` are skipped.
   Exclusions match by name at any depth.
5. Each file becomes a subsection titled after its name: the extension is dropped, `-`, `_` and
   spaces become spaces, and everything is lowercased (`modular_binomial_coefficient.cpp` becomes
   "modular binomial coefficient"). Files inside subfolders get a prefix, e.g. "2D / point2d".
6. Within a section, files are sorted alphabetically, except those listed in
   `file_names_to_sort_first` (by their display name), which go first.
7. The generated Typst source is compiled using the layout in `.typst/template.typ`
   (title, header, table of contents, columns and code-block styling).

### Customizing

Everything is controlled from `config.yaml`:

| Key | Meaning |
| --- | --- |
| `out` | Output file name |
| `university`, `team` | Shown in the page header |
| `theme` | Syntax-highlighting theme, one of `.typst/themes/*.tmTheme` (`Afterglow`, `Custom`, `Dracula`, `Inspired`) |
| `paper`, `portrait`, `margin` | Page setup (`portrait: false` means landscape) |
| `font_size`, `column_count`, `column_gutter` | Text size and column layout |

To add a new template to the notebook, put it in one of the `sections` folders with a supported
extension and rebuild. To keep a file out of the notebook, add its file name to `exclude_files`.

## Other folders

- `Solved problems/`: solutions to individual problems, plus written explanations in
  `Solved problems/Explanations/`. Not included in the notebook.
- `Tests/`: tests for the templates. See [`Tests/README.md`](Tests/README.md).
