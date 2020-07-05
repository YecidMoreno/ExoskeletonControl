/*
 * File: _coder_m2cpp_info.c
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 30-May-2020 03:24:07
 */

/* Include Files */
#include "_coder_m2cpp_info.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : const mxArray *
 */
const mxArray *emlrtMexFcnResolvedFunctionsInfo()
{
  const mxArray *nameCaptureInfo;
  const char * data[12] = {
    "789ced5c4d6f1b4518deb469941e28b980401ca804424245dec449ec0484e47a6d276be2c4899dc6248266bd3b8e379efdc87ea48e2fe427f0037ae81171e2d8"
    "63b921ee70e0843872e1c4b561bfc61fdb4cbcad376b369e919cf1f8b5e779e7f5b3ef3cf3da0e35c596a6288aba67dd6e5bb76755ca696fb91d35e7f5b7a8c1",
    "e6b74f79fd3ddf18b53bd4f4c0eb90fda9d7f38a6c80b6e10ea028834d53aa03cd1ac89c04bad3088a24ca9c6c54cf5440694057e029101c4b4384a02a4a6043"
    "e91bac8bd6402af499ba03db64df679a806f554c89d29a7acf5dd83f40eb72e28359ff74c0f87c81898ffdbc97dff5ec07f96f98cfe95cfe11cd4a6bbbec63c6",
    "8a8fa640ba6e8a50a04b9c01b93a5de1355135743a072030002d2579554d4803fe1e62fc9909e8afbf47ed2e35db3fcc0cc30b1a9f3b18bc39cb62c78757a022"
    "53c3d717146fc637eee1cd38788262d621e8e1fd34225e118be7beffc87ec06ed41c0a9435e548e3a4fb365775baacc0335de57840ef24e7175639da50145857",
    "da3490200dc53a2db9cc50549d7642e5d121423e649efef5d1ef0f23e65fd47c1f1b5e1b335f50febd8bc143fc4376a67304596ef1ab5ab5a8768e17e645912b"
    "ee177a7e9487e00cf383c28ca39a3feed7318e074179771be3ff5daf7f6fe0d1c58cd39d335e9febe6fb730c4ed0387e88f103c511d97945005a42b444822673",
    "3021ea596b233458d992094013f9b1ed07bf8c88d7c0e2b9eb47f6d7e591dee43420d04ed8bcbf0fbc0e0591f607d1e6588479ed57ea25d927e2be4f3cd9cfee"
    "763aed667a4b35f3f924c32fef702b59b24ffc5ff689438c7fe1f26e95e8ff8078379f0f44ff5f271ed1ffe1cc4faee3cbfd1fe0dd8b4a64795dd4652ece797d",
    "038be7f201d947e40380d61dda0996cb88e8f870fefcdf3f7e2379fd9af046cdebef60f010ff90fde4a1b9252d9dd596e677b4a4c92c80d553699322797d72ae"
    "63bb7d4cea3714a9df5cb52e52bf192f1ea9df84337fdc75be8af12f28ef6ef9c6a8a13aff5cff832faa19a7cfec46a8fb45d9ce9144f707d20b56b088eebf49",
    "7851e5f9e57609165aa7c2319baab58b82965c922b2952cf99a0ebd86e44f713dd7ff5ba88ee1f2f1ed1fde1cc1f77dd7f88f12fdcfa7e743abf0115c5fe362f"
    "d1f943f441c39469275891eb839f773f213a3fee797de524bd553d81b9e556b659dd5eab1827b91c4f74fe245dc756bb4f743e4574fe55eb223a7fbc7844e787",
    "333fd90f2ef7ffbaea3e1f60f050bc90ddb71fe83c07392d814e01a39f03fc0de70f6a08eff91be2a1f96b43f090fd4df862df5ed9041eb8a143dc89b0eeffe3"
    "defbe43c10f7fc5f6fa6ca35191a424591f2a6bcbe58cf678b6b24ff4f6afeff1e335fd0787d8ac143f142765ffee754159e559c4c563065de10159995cbd00a",
    "9cf7fc619f7707f5efed21fe217bc3f3e271939305ebc010d67901f8c67e7c640f6d7fc047d6215a843cdbdefb9b9c17e2be5f98658669a7993d75b3ba0cd29b"
    "cdc5d246bac5dc9cfd825cdf97af2b181f3f0bedf38259df98ea3e6fd6fb5e9015264d07e3aa1b8d7a4ed8c6e2b93c41f61175851d245b59a070a18f91a2fcbd",
    "d7ec97df92bc1ff7bcff648fd50bb0f5a8906c6815787abc55943bdb24ef93bcefb4c48dab1f8d6b5f20f5a3ebc273dba4e091fa5138f33fc3bc7eb2ff9fdb5c"
    "683a7fda37ee22581627bf8aba53f219573eff6144bc2c16cf7dff91fd80ad95b2af91cf3d7d0f39f988b66314fdf7c3febcb8b8f827c2fc3d597851e56f8385",
    "4dd8e62bfb0b4b294984eba995edf2d7ebf1cfdfff019634921e", "" };

  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(data, 21688U, &nameCaptureInfo);
  return nameCaptureInfo;
}

/*
 * Arguments    : void
 * Return Type  : mxArray *
 */
mxArray *emlrtMexFcnProperties()
{
  mxArray *xResult;
  mxArray *xEntryPoints;
  const char * fldNames[6] = { "Name", "NumberOfInputs", "NumberOfOutputs",
    "ConstantInputs", "FullPath", "TimeStamp" };

  mxArray *xInputs;
  const char * b_fldNames[4] = { "Version", "ResolvedFunctions", "EntryPoints",
    "CoverageInfo" };

  xEntryPoints = emlrtCreateStructMatrix(1, 1, 6, *(const char * (*)[6])&
    fldNames[0]);
  xInputs = emlrtCreateLogicalMatrix(1, 0);
  emlrtSetField(xEntryPoints, 0, "Name", emlrtMxCreateString("m2cpp"));
  emlrtSetField(xEntryPoints, 0, "NumberOfInputs", emlrtMxCreateDoubleScalar(0.0));
  emlrtSetField(xEntryPoints, 0, "NumberOfOutputs", emlrtMxCreateDoubleScalar
                (0.0));
  emlrtSetField(xEntryPoints, 0, "ConstantInputs", xInputs);
  emlrtSetField(xEntryPoints, 0, "FullPath", emlrtMxCreateString(
    "C:\\DEV\\ImGUI_Control\\build\\Matlab\\Scripts\\Delete\\m2cpp.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp", emlrtMxCreateDoubleScalar
                (737941.14098379633));
  xResult = emlrtCreateStructMatrix(1, 1, 4, *(const char * (*)[4])&b_fldNames[0]);
  emlrtSetField(xResult, 0, "Version", emlrtMxCreateString(
    "9.6.0.1072779 (R2019a)"));
  emlrtSetField(xResult, 0, "ResolvedFunctions", (mxArray *)
                emlrtMexFcnResolvedFunctionsInfo());
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

/*
 * File trailer for _coder_m2cpp_info.c
 *
 * [EOF]
 */
