#let compose(
  args,
) = {
  // Document config
  let conf = args.conf
  
  set page(flipped: not conf.portrait, margin: conf.margin, paper: conf.paper)
  set text(font: "New Computer Modern")
  show raw: set text(font: "DejaVu Sans Mono", weight: 500, size: 6.984pt)
  set raw(theme: "themes/"+conf.theme+".tmTheme") if conf.theme != ""
  
  // Title
  
  align(center, {
    text(size: 10mm)[Team Notebook]
    v(-3mm)
    text(size: 6mm, conf.university + " - " + conf.team)
  })
  
  // Index
  
  place(columns(conf.column_count, gutter: conf.column_gutter, {
    for i in range(conf.column_count - 1) {
      colbreak()
      align(left+top, move(line(angle: 90deg, length: 164mm), dx: -conf.column_gutter/2))
    }
  }))
  columns(conf.column_count, gutter: conf.column_gutter, {
    show outline.entry.where(level: 1): set text(weight: "bold")
    outline(title: none, indent: 5mm)
  })
  
  // Body setup
  
  pagebreak(weak: true)
  
  set page(header: {
    align(left, move(conf.university + " - " + conf.team, dy: 100%))
    align(right, move(context counter(page).display()))
  })
  /*#set page(background: pad(margin, {
    columns(cols, gutter: gutter, {
      for i in range(cols - 1) {
        colbreak()
        align(left+top, move(line(angle: 90deg, length: 100%), dx: -gutter/2))
      }
    })
  }))*/
  show: columns.with(conf.column_count, gutter: conf.column_gutter)
  
  set heading(numbering: "1.1")
  
  let codeblock(title, code) = [
    == #title

    #block(
      code,
      stroke: 1pt,
      radius: 1mm,
      width: 100%,
      outset: 1.5mm,
      breakable: true,
    )
  ]
  
  // Body contents
  for (sname, blocks) in args.content [
    = #sname

    #for (title, code) in blocks {
      codeblock(title, code)
    }
  ]
}
