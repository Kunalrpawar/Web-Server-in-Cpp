# Static Files Directory

This directory contains all the static files served by the C++ web server.

## Files:
- `index.html` - Main homepage
- `style.css` - CSS styling
- `script.js` - JavaScript functionality
- `admin.html` - Admin panel
- `README.md` - This file

## How it works:
The server automatically serves files from this directory based on the URL path.
For example:
- `http://localhost:8080/` → serves `index.html`
- `http://localhost:8080/style.css` → serves `style.css`
- `http://localhost:8080/admin` → serves `admin.html`

## Adding new files:
Simply place any HTML, CSS, JS, or image files in this directory and they will be automatically served by the server. 