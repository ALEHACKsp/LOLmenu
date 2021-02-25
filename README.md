# LOLmenu

# THIS IS BASED OFF VA-LOL-RANT MADE BY @pean153 https://www.unknowncheats.me/forum/valorant/414174-va-lol-rant-internal-external-aimassist.html

# Intructions:
1. Download [interception](https://github.com/oblitum/Interception)
2. Go into Interception > library > x86
3. Copy interception.dll to any folder you want
4. Set a path system variable (if you don't know how google is your friend) to the folder you copied interception.dll to
5. Open your cmd
6. Navigate to Interception > command line installer
7. type - install-interception /install
8. Restart your pc
9. Build the dll yourself (If any errors please look through the forum. The most common error is \_CRT_SECURE_NO_WARNINGS and a LINK error. Just for convenience see below on how to fix them. Otherwise use your brain :])
10. Inject into a 32-bit proccess

# ERROR FIXES (SKIP THIS PART IF YOU DON'T GET ERRORS WHEN BUILDING)
        - for _CRT_SECURE_NO_WARNINGS go to the dll properties > C/C++ > preprocessor > in the Preprocessor Definitions add _CRT_SECURE_NO_WARNINGS
        - for a LINK error go to the dll properties > Linker > General > under Additional Library Directories add a path to Interception > Library > x86.

# GENERAL INFO
NOTHING is set to default. Set every setting yourself, then commit the changes. If you skip over a setting, it won't work correctly. It doesn't tell you if you missed a step. It will, however, tell you if you've entered something wrong.

If you want the cheat always on, set your toggle key to be a toggle, press your key, and leave it on.

**RED ISN'T IMPLEMENTED**
**EVERYTHING IS CASE SENSITIVE. WHEN ENTERING YOUR SELECTION (e.g., CHEST, NECK, HEAD), TYPE IT IN ALL CAPS; OTHERWISE, IT WON'T GO THROUGH. THE PROGRAM SHOULD TELL YOU IF WHAT YOU'VE ENTERED IS INVALID.**

# KNOWN BUGS
**WHEN SELECTING YOUR TOGGLE-KEY SOMETHING COMES UP SAYING "ENTER CHAR TO COPY UP TO: "**
- It's safe to ignore this; press any key to get rid of it and continue to enter your selection.
- I don't know what causes this. If you see something feel free to let me know in the forum :)

# ENJOY :D
