- Add more tests and find any bugs in mortgage/home payment logic
- Add tests and logic for house appreciation
- Finish implementing the simulation runner
- Add a make target to run the simulation
- Design and implement Market and Portfolio for fancier simulation
    - Can have:
        1. static regimes for lifetime of mortgage
        2. cyclical regimes
        3. randomized regimes
    - Simulation logic should be flexible enough to just read each year's house price appreciation and stock market performance from the relevant Market object (or whatever object ends up managing those parameters) and apply it.
- Finish the README documentation 