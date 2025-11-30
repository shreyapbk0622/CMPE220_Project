# Converting PROJECT_REPORT.md to PDF

## Before Converting

1. **Fill in the placeholders** in PROJECT_REPORT.md:
   - Team member names (appears in 3 places)
   - Instructor name
   - Submission date
   - Video link
   - GitHub repository URL (if different)
   - Specific contributions for each team member

2. **Update team member sections** with actual names and contributions

## Method 1: Using Pandoc (Recommended)

### Install Pandoc
**macOS:**
```bash
brew install pandoc
brew install basictex  # For LaTeX support
```

**Linux:**
```bash
sudo apt-get install pandoc texlive-latex-base texlive-latex-extra
```

**Windows:**
Download from https://pandoc.org/installing.html

### Convert with Proper Formatting

```bash
pandoc PROJECT_REPORT.md \
  -o PROJECT_REPORT.pdf \
  --pdf-engine=xelatex \
  -V geometry:margin=1in \
  -V linestretch=2.0 \
  -V pagestyle=plain \
  --number-sections \
  --toc \
  --toc-depth=2
```

**Options explained:**
- `-V geometry:margin=1in` - Sets 1-inch margins (required)
- `-V linestretch=2.0` - Double spacing (required)
- `-V pagestyle=plain` - Adds page numbers (required)
- `--number-sections` - Numbers all sections
- `--toc` - Adds table of contents
- `--toc-depth=2` - TOC shows up to 2 levels

## Method 2: Using VSCode with Extensions

### Install Extensions
1. Open VSCode
2. Install "Markdown PDF" extension by yzane
3. Open PROJECT_REPORT.md
4. Right-click → "Markdown PDF: Export (pdf)"

### Configure Settings (for double-spacing)
Add to VSCode settings.json:
```json
{
  "markdown-pdf.styles": [
    "body { line-height: 2.0; }"
  ],
  "markdown-pdf.displayHeaderFooter": true,
  "markdown-pdf.footerTemplate": "<div style='font-size:10px; text-align:center; width:100%;'>Page <span class='pageNumber'></span> of <span class='totalPages'></span></div>"
}
```

## Method 3: Using Google Docs

1. Copy content from PROJECT_REPORT.md
2. Go to https://docs.google.com
3. Create new document
4. Paste content
5. Format → Line spacing → Double
6. Format → Page numbers → Bottom of page
7. File → Page setup → Margins: 1 inch all sides
8. File → Download → PDF Document

## Method 4: Using Microsoft Word

1. Copy content from PROJECT_REPORT.md
2. Open Microsoft Word
3. Paste content
4. Home → Line and Paragraph Spacing → 2.0
5. Insert → Page Number → Bottom of Page
6. Layout → Margins → Normal (1" all sides)
7. File → Save As → PDF

## Method 5: Online Markdown to PDF Converter

### Using Markdown to PDF (with styling)
1. Go to https://www.markdowntopdf.com/
2. Upload PROJECT_REPORT.md
3. Add custom CSS for double-spacing:
```css
body {
  line-height: 2.0;
  margin: 1in;
}
```
4. Download PDF

### Using Dillinger
1. Go to https://dillinger.io/
2. Paste markdown content
3. Export → Styled HTML
4. Open HTML in browser
5. Print → Save as PDF
6. Set margins to 1 inch in print dialog

## Verification Checklist

After conversion, verify your PDF has:
- ✅ Double-spaced text throughout
- ✅ Page numbers on every page (usually bottom center)
- ✅ 1-inch margins on all sides
- ✅ All team member names filled in
- ✅ GitHub repository link
- ✅ Video link
- ✅ Specific contributions for each team member
- ✅ All sections present (Title, GitHub, How-to, Contributions, Summary)
- ✅ Page breaks between major sections

## Tips for Best Results

1. **Preview before final conversion** - Always check the output

2. **Check page numbers** - Ensure they appear on every page

3. **Verify margins** - Open PDF properties and check page size/margins

4. **Test links** - Click GitHub and video links to ensure they work

5. **Proofread** - Check for any formatting issues or missing content

6. **File size** - Keep under 10MB for easy submission

## Troubleshooting

**Problem: No page numbers**
- Solution: Ensure you're using a PDF generator that supports headers/footers

**Problem: Not double-spaced**
- Solution: Add `line-height: 2.0` in CSS or use `-V linestretch=2.0` in Pandoc

**Problem: Margins too small/large**
- Solution: Specify margins explicitly: `geometry:margin=1in` or adjust in Word/Docs

**Problem: Page breaks not working**
- Solution: Some converters don't support `<div style="page-break-after: always;">`. You may need to insert manual page breaks after conversion

## Recommended Workflow

For best quality and meeting all requirements:

1. **Edit** PROJECT_REPORT.md with all your information
2. **Convert** using Pandoc with the command above
3. **Open** PDF in Adobe Acrobat or Preview
4. **Verify** all requirements (spacing, margins, page numbers)
5. **Adjust** if needed and reconvert
6. **Submit** final PDF

## Example Pandoc Command with All Options

```bash
pandoc PROJECT_REPORT.md \
  -o "CMPE220_CPU_Project_Report.pdf" \
  --pdf-engine=xelatex \
  -V geometry:margin=1in \
  -V linestretch=2.0 \
  -V pagestyle=plain \
  -V fontsize=12pt \
  -V documentclass=article \
  --number-sections \
  --toc \
  --toc-depth=2 \
  --highlight-style=tango
```

This produces a professional PDF with:
- Double spacing
- 1-inch margins
- Page numbers
- 12pt font
- Numbered sections
- Table of contents
- Syntax highlighting for code

---

**Need Help?**

If you have issues converting, you can:
1. Ask your team members to try their method
2. Use the university computer lab (usually has full LaTeX/Pandoc setup)
3. Convert to Word first, then format and save as PDF
