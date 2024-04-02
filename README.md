# Dungeon-Generator
Work in progress class that will output an array of data that could be interpreted as a floor plan
This class is a proof of concept, and inputs or outputs may need to be adjusted project by project.

### Some terms used and their definitions
- Dungeon: An underground floor plan where rooms are linked by hallways that may have a length of 0 or more.
- Village: An aboveground floor plan where rooms are grouped together into houses, and hallways outside of those houses are open and have a length of 1 or more.
- Ruins: An aboveground floor plan where rooms are grouped together into a single structure, hallways outside of this structure do not exist, and rooms inside of the structure are linked by hallways that may have a length of 0 or more.

## Things still needing to be done:
- Bring in my implementation of Bresenham's line algorithm from the LOS algorithm for hallways
- Generate rooms intelligently rather than purely randomly
- Allow for generation of things like villages
- Allow for more complicated shapes besides boxes and circles (like an L shape or + shape)
- Allow for 'archetypes' with generation, so things are generated with a certain style
- Allow for generation of things like ruins
