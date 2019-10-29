xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 79;
 0.00000;0.00000;-0.21207;,
 0.00000;-0.12896;-1.60261;,
 -0.90784;-0.12896;-1.19533;,
 0.00000;0.00000;-0.21207;,
 -1.28388;-0.12896;-0.21207;,
 0.00000;0.00000;-0.21207;,
 -0.90784;-0.12896;0.77119;,
 0.00000;0.00000;-0.21207;,
 0.00000;-0.12896;1.17846;,
 0.00000;0.00000;-0.21207;,
 0.90784;-0.12896;0.77119;,
 0.00000;0.00000;-0.21207;,
 1.28388;-0.12896;-0.21207;,
 0.00000;0.00000;-0.21207;,
 0.90784;-0.12896;-1.19533;,
 0.00000;0.00000;-0.21207;,
 0.00000;-0.12896;-1.60261;,
 0.00000;-0.49619;-2.78144;,
 -1.67747;-0.49619;-2.02889;,
 -2.37230;-0.49619;-0.21207;,
 -1.67747;-0.49619;1.60475;,
 0.00000;-0.49619;2.35730;,
 1.67747;-0.49619;1.60475;,
 2.37230;-0.49619;-0.21207;,
 1.67747;-0.49619;-2.02889;,
 0.00000;-0.49619;-2.78144;,
 0.00000;-1.49179;-6.15305;,
 -2.19172;-1.49179;-4.78650;,
 -3.09956;-1.49179;-1.48735;,
 -2.19172;-1.49179;1.81180;,
 0.00000;-1.49179;3.17836;,
 2.19172;-1.49179;1.81180;,
 3.09956;-1.49179;-1.48735;,
 2.19172;-1.49179;-4.78650;,
 0.00000;-1.49179;-6.15305;,
 0.00000;-2.51246;-6.53747;,
 -2.37230;-2.51246;-5.05832;,
 -3.35494;-2.51246;-1.48735;,
 -2.37230;-2.51246;2.08363;,
 0.00000;-2.51246;3.56278;,
 2.37230;-2.51246;2.08363;,
 3.35494;-2.51246;-1.48735;,
 2.37230;-2.51246;-5.05832;,
 0.00000;-2.51246;-6.53747;,
 0.00000;-3.53313;-6.15305;,
 -2.19172;-3.53313;-4.78650;,
 -3.09956;-3.53313;-1.48735;,
 -2.19172;-3.53313;1.81180;,
 0.00000;-3.53313;3.17836;,
 2.19172;-3.53313;1.81180;,
 3.09956;-3.53313;-1.48735;,
 2.19172;-3.53313;-4.78650;,
 0.00000;-3.53313;-6.15305;,
 0.00000;-4.39842;-5.05832;,
 -1.67747;-4.39842;-4.01241;,
 -2.37230;-4.39842;-1.48735;,
 -1.67747;-4.39842;1.03771;,
 0.00000;-4.39842;2.08363;,
 1.67747;-4.39842;1.03771;,
 2.37230;-4.39842;-1.48735;,
 1.67747;-4.39842;-4.01241;,
 0.00000;-4.39842;-5.05832;,
 0.00000;-4.97658;-3.41995;,
 -0.90784;-4.97658;-2.85390;,
 -1.28388;-4.97658;-1.48735;,
 -0.90784;-4.97658;-0.12080;,
 0.00000;-4.97658;0.44524;,
 0.90784;-4.97658;-0.12080;,
 1.28388;-4.97658;-1.48735;,
 0.90784;-4.97658;-2.85390;,
 0.00000;-4.97658;-3.41995;,
 0.00000;-5.17961;-1.48735;,
 0.00000;-5.17961;-1.48735;,
 0.00000;-5.17961;-1.48735;,
 0.00000;-5.17961;-1.48735;,
 0.00000;-5.17961;-1.48735;,
 0.00000;-5.17961;-1.48735;,
 0.00000;-5.17961;-1.48735;,
 0.00000;-5.17961;-1.48735;;
 
 64;
 3;0,1,2;,
 3;3,2,4;,
 3;5,4,6;,
 3;7,6,8;,
 3;9,8,10;,
 3;11,10,12;,
 3;13,12,14;,
 3;15,14,16;,
 4;1,17,18,2;,
 4;2,18,19,4;,
 4;4,19,20,6;,
 4;6,20,21,8;,
 4;8,21,22,10;,
 4;10,22,23,12;,
 4;12,23,24,14;,
 4;14,24,25,16;,
 4;17,26,27,18;,
 4;18,27,28,19;,
 4;19,28,29,20;,
 4;20,29,30,21;,
 4;21,30,31,22;,
 4;22,31,32,23;,
 4;23,32,33,24;,
 4;24,33,34,25;,
 4;26,35,36,27;,
 4;27,36,37,28;,
 4;28,37,38,29;,
 4;29,38,39,30;,
 4;30,39,40,31;,
 4;31,40,41,32;,
 4;32,41,42,33;,
 4;33,42,43,34;,
 4;35,44,45,36;,
 4;36,45,46,37;,
 4;37,46,47,38;,
 4;38,47,48,39;,
 4;39,48,49,40;,
 4;40,49,50,41;,
 4;41,50,51,42;,
 4;42,51,52,43;,
 4;44,53,54,45;,
 4;45,54,55,46;,
 4;46,55,56,47;,
 4;47,56,57,48;,
 4;48,57,58,49;,
 4;49,58,59,50;,
 4;50,59,60,51;,
 4;51,60,61,52;,
 4;53,62,63,54;,
 4;54,63,64,55;,
 4;55,64,65,56;,
 4;56,65,66,57;,
 4;57,66,67,58;,
 4;58,67,68,59;,
 4;59,68,69,60;,
 4;60,69,70,61;,
 3;62,71,63;,
 3;63,72,64;,
 3;64,73,65;,
 3;65,74,66;,
 3;66,75,67;,
 3;67,76,68;,
 3;68,77,69;,
 3;69,78,70;;
 
 MeshMaterialList {
  4;
  64;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.360000;0.360000;0.360000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.120000;0.120000;0.120000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "TEX\\canx2.jpg";
   }
  }
  Material {
   1.000000;0.569000;0.192000;1.000000;;
   5.000000;
   0.500000;0.500000;0.500000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  62;
  -0.000000;1.000000;0.000000;,
  0.000000;0.980694;-0.195547;,
  -0.149253;0.979110;-0.138082;,
  -0.210785;0.977532;0.000000;,
  -0.149252;0.979110;0.138083;,
  0.000000;0.980694;0.195547;,
  0.149252;0.979110;0.138083;,
  0.210785;0.977532;0.000000;,
  0.149253;0.979110;-0.138082;,
  0.000000;0.954386;-0.298575;,
  -0.312269;0.920704;-0.234078;,
  -0.567535;0.823066;0.021600;,
  -0.477713;0.780246;0.403740;,
  0.000000;0.810512;0.585722;,
  0.477713;0.780246;0.403740;,
  0.567535;0.823066;0.021600;,
  0.312269;0.920704;-0.234078;,
  0.000000;0.748537;-0.663093;,
  -0.628376;0.638402;-0.444506;,
  -0.896958;0.441591;0.021507;,
  -0.726762;0.392277;0.563857;,
  0.000000;0.461340;0.887223;,
  0.726762;0.392277;0.563857;,
  0.896958;0.441591;0.021507;,
  0.628376;0.638402;-0.444506;,
  -0.529088;0.000000;-0.848567;,
  -0.803927;0.000000;-0.594727;,
  -1.000000;-0.000000;-0.000000;,
  -0.803928;0.000000;0.594727;,
  -0.529088;0.000000;0.848567;,
  0.803928;-0.000000;0.594727;,
  1.000000;-0.000000;-0.000000;,
  0.803927;0.000000;-0.594727;,
  -0.187290;-0.656996;-0.730259;,
  -0.693166;-0.516356;-0.502889;,
  -0.889966;-0.456026;0.000000;,
  -0.693166;-0.516356;0.502889;,
  -0.187290;-0.656997;0.730258;,
  0.693166;-0.516356;0.502889;,
  0.889966;-0.456026;-0.000000;,
  0.693166;-0.516356;-0.502889;,
  0.000000;-0.877575;-0.479439;,
  -0.464017;-0.824775;-0.323162;,
  -0.627832;-0.778349;0.000000;,
  -0.464017;-0.824775;0.323162;,
  0.000000;-0.877575;0.479439;,
  0.464017;-0.824775;0.323162;,
  0.627832;-0.778349;0.000000;,
  0.464017;-0.824775;-0.323162;,
  0.000000;-0.975714;-0.219047;,
  -0.226443;-0.961930;-0.153018;,
  -0.316413;-0.948621;0.000000;,
  -0.226442;-0.961930;0.153018;,
  0.000000;-0.975714;0.219047;,
  0.226442;-0.961930;0.153018;,
  0.316413;-0.948621;-0.000000;,
  0.226443;-0.961930;-0.153018;,
  0.000000;-1.000000;0.000000;,
  0.529088;0.000000;0.848567;,
  0.529088;0.000000;-0.848567;,
  0.503975;-0.304429;0.808289;,
  0.503975;-0.304428;-0.808290;;
  64;
  3;0,1,2;,
  3;0,2,3;,
  3;0,3,4;,
  3;0,4,5;,
  3;0,5,6;,
  3;0,6,7;,
  3;0,7,8;,
  3;0,8,1;,
  4;1,9,10,2;,
  4;2,10,11,3;,
  4;3,11,12,4;,
  4;4,12,13,5;,
  4;5,13,14,6;,
  4;6,14,15,7;,
  4;7,15,16,8;,
  4;8,16,9,1;,
  4;9,17,18,10;,
  4;10,18,19,11;,
  4;11,19,20,12;,
  4;12,20,21,13;,
  4;13,21,22,14;,
  4;14,22,23,15;,
  4;15,23,24,16;,
  4;16,24,17,9;,
  4;17,25,26,18;,
  4;18,26,27,19;,
  4;19,27,28,20;,
  4;20,28,29,21;,
  4;21,58,30,22;,
  4;22,30,31,23;,
  4;23,31,32,24;,
  4;24,32,59,17;,
  4;25,33,34,26;,
  4;26,34,35,27;,
  4;27,35,36,28;,
  4;28,36,37,29;,
  4;58,60,38,30;,
  4;30,38,39,31;,
  4;31,39,40,32;,
  4;32,40,61,59;,
  4;33,41,42,34;,
  4;34,42,43,35;,
  4;35,43,44,36;,
  4;36,44,45,37;,
  4;37,45,46,38;,
  4;38,46,47,39;,
  4;39,47,48,40;,
  4;40,48,41,33;,
  4;41,49,50,42;,
  4;42,50,51,43;,
  4;43,51,52,44;,
  4;44,52,53,45;,
  4;45,53,54,46;,
  4;46,54,55,47;,
  4;47,55,56,48;,
  4;48,56,49,41;,
  3;49,57,50;,
  3;50,57,51;,
  3;51,57,52;,
  3;52,57,53;,
  3;53,57,54;,
  3;54,57,55;,
  3;55,57,56;,
  3;56,57,49;;
 }
 MeshTextureCoords {
  79;
  0.062500;0.000000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
