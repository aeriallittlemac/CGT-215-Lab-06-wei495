# CGT 215 – Lab 06: Green-Screen Sprite Compositing (SFML)

A C++ program using SFML that loads a background image and a
foreground "sprite" image, removes the foreground's green-screen
background via chroma keying, and composites the result into a
window.

## What It Does

1. Loads a background image (`images1/backgrounds/alebrije.png`) and a
   foreground image (`images1/characters/yoda.png`).
2. Copies the foreground texture into an `Image` so individual pixels
   can be inspected and modified.
3. Samples the color at the foreground image's bottom-right corner
   pixel and treats it as the "green screen" key color.
4. Walks every pixel in the foreground image; any pixel matching the
   key color has its alpha set to `0` (fully transparent).
5. Opens a `1024x768` window, draws the background first, then draws
   the modified (transparent-keyed) foreground on top — producing a
   composited image where the foreground's background is invisible
   and the background image shows through.
6. Displays the result and loops forever (`while (true);`) to keep the
   window open.

## Requirements

- **SFML** (Simple and Fast Multimedia Library), specifically the
  Graphics module (`SFML/Graphics.hpp`), linked against your compiler.
- A C++ compiler with SFML properly configured (include paths, lib
  paths, and required DLLs/shared libraries for `sfml-graphics`,
  `sfml-window`, `sfml-system`).
- The following image assets, present relative to the working
  directory at runtime:
  - `images1/backgrounds/alebrije.png`
  - `images1/characters/yoda.png`

## Usage

1. Ensure SFML is installed and linked (see SFML's official setup
   docs for your IDE/compiler).
2. Place the required image files in `images1/backgrounds/` and
   `images1/characters/` relative to the executable's working
   directory.
3. Build and run the program.
4. A window titled **"Here's the output"** opens showing the
   background with the foreground character composited on top, green
   background removed.
5. Close the window via your OS window controls or terminate the
   process — the program does not handle window close events (see
   Known Quirks).

## Files

| File | Description |
|------|--------------|
| `CGT-215-Lab-06-wei495.cpp` | Main source file: loads textures, performs chroma-key transparency on the foreground image, and renders the composited scene in an SFML window. |

## Known Quirks / Possible Improvements

- **No event loop / can't close cleanly:** `while (true);` spins
  forever and never polls `window.pollEvent(...)`, so clicking the
  window's close button does nothing — the process must be killed
  externally. A proper SFML event loop (checking for
  `Event::Closed`) would fix this.
- **Key color sampled every pixel:** the key (green) color is
  re-read from the corner pixel inside the innermost loop on every
  iteration instead of once before the loops — functionally harmless
  here but wasteful.
- **Exact color match only:** a pixel must match the sampled key
  color *exactly* to become transparent, so anti-aliased edges or
  slightly varying shades of green around the character will not be
  keyed out, potentially leaving a visible fringe.
- **Hard-coded file paths:** background and foreground paths are
  fixed in code; the program exits with an error message if either
  file isn't found at those relative paths.
- **No cleanup:** the infinite loop means the window/resources are
  never explicitly released; the program relies on the OS to reclaim
  resources when the process is terminated.
