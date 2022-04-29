# Deploy How To

1. Change to `Release` mode in `Qt Creator` with `Build Configuration`;
2. Click `Run`;
3. Generate `build-QtHowTo-Desktop_Qt_5_15_2_MinGW_64_bit-Release` outside the project;
4. Copy `QtHowTo.exe` from directory `release` inside it to directory `DeployHowTo`;
5. Open `Qt Terminal`;
6. Type `cd /d E:\UsefulTools\Codes\QtHowTo\DeployHowTo`;
7. Type `windeployqt QtHowTo.exe`;
8. Done.