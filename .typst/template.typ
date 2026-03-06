#let compose(
  args,
) = {
  // Document config
  let conf = args.conf
  
  set page(flipped: not conf.portrait, margin: conf.margin, paper: conf.paper)
  
  set page(header: {
    align(left, move(conf.university + " - " + conf.team, dy: 100%))
    align(right, move(context counter(page).display()))
  })

  set text(font: "New Computer Modern")
  show raw: set text(font: "DejaVu Sans Mono", weight: 500, size: 6.984pt)
  set raw(theme: "themes/"+conf.theme+".tmTheme") if conf.theme != ""
  
  // Title
  align(center, {
    text(size: 10mm)[Team Notebook]
    v(-3mm)
    text(size: 6mm, conf.university + " - " + conf.team)
  })
  
  // Vertical line decorations (Placed in the background)
  place(columns(conf.column_count, gutter: conf.column_gutter, {
    for i in range(conf.column_count - 1) {
      colbreak()
      align(left+top, move(line(angle: 90deg, length: 164mm), dx: -conf.column_gutter/2))
    }
  }))
  
  // --- COMBINED COLUMNS FOR INDEX AND BODY ---
  columns(conf.column_count, gutter: conf.column_gutter, {
    
    // 1. Index
    show outline.entry.where(level: 1): set text(weight: "bold")
    outline(title: none, indent: 5mm)
    
    // Add a tiny bit of space between the index and the first section
    v(1em) 

    // 2. Body setup
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
    
    // 3. Body contents
    for (sname, blocks) in args.content [
      = #sname
      #for (title, code) in blocks {
        codeblock(title, code)
      }
    ]
    
  }) // End of combined columns block
}