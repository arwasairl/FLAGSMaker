# Automated FLAG/XML file generator for MSFS2020 & MSFS2024.

Limitations:
1. Files supported are ONLY PNGs and COMP textures. ALBD, NORM, and other texture file types like TGA, DDS, EXR, etc. are not supported
2. The current FLAG/XML parameters is ONLY "_DEFAULT=QUALITYHIGH" or "<UserFlags Type="_DEFAULT">QUALITYHIGH</UserFlags>"; If you want to add more parameters, such as NOREDUCE or ALPHAPRESERVATION, you will have to manually edit the code to add those parameters.
3. The textures within your texture directory MUST have a suffix "COMP" for QUALITYHIGH flags.

Notes:
1. For MSFS2024, the XML for Albedo and Normal textures is only: <BitmapConfiguration><BitmapSlot>MTL_BITMAP_DECAL0</BitmapSlot></BitmapConfiguration>.

Version History<br/>
[2025-11-06] 1.3 - Removed copyright information, added support for lowercased texture filenames.<br/>
[2025-08-11] 1.2 - Removed copyright information, added support for lowercased texture filenames.<br/>
[2024-09-08] 1.1 - Fixed bug where no feedback was generated for FLAG files lower down the file hierarchy<br/>
[2024-09-08] 1.0 - Initial release
