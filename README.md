# Automated FLAG file generator for MSFS2020/2024.

Limitations:
1. Files supported are ONLY PNGs and COMP textures. ALBD, NORM, and other texture file types like TGA, DDS, EXR, etc. are not supported
2. The current FLAG parameters is ONLY "_DEFAULT=QUALITYHIGH"; If you want to add more parameters, such as NOREDUCE or ALPHAPRESERVATION, you will have to manually edit the generated FLAGS file, or edit the code to add those parameters.

Version History
[2024-09-08] 1.1 - Fixed bug where no feedback was generated for FLAG files lower down the file hierarchy
[2024-09-08] 1.0 - Initial release