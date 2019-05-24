#ifndef __state_h__ 
#define __state_h__ 

#define __state_h__VERSION 0x60b5909b 

#define __GL_NUMBER_OF_TEXTURE_TARGETS 6
#define __GL_TEXTURE_INDEX_1D 0
#define __GL_TEXTURE_INDEX_2D 1
#define __GL_TEXTURE_INDEX_3D 2
#define __GL_PROXY_TEXTURE_INDEX_1D 3
#define __GL_PROXY_TEXTURE_INDEX_2D 4
#define __GL_PROXY_TEXTURE_INDEX_3D 5
#define __GL_MAX_TMU_COUNT 4
#define __GL_PERFORM_NOP 0
#define __GL_PERFORM_DESTROY_BUFFERS 1
#define __GL_PERFORM_CREATE_BUFFERS 2


typedef struct __glCoordRec __glCoord;
typedef struct __glColorRec __glColor;
typedef struct __glMaterialStateRec __glMaterialState;
typedef struct __glPerLightStateRec __glPerLightState;
typedef struct __glLightStateRec __glLightState;
typedef struct __glPolygonStateRec __glPolygonState;
typedef struct __glDepthStateRec __glDepthState;
typedef struct __glColorStateRec __glColorState;
typedef struct __glStencilStateRec __glStencilState;
typedef struct __glTextureCoordStateRec __glTextureCoordState;
typedef struct __glXformStateRec __glXformState;
typedef struct __glViewportStateRec __glViewportState;
typedef struct __glScissorStateRec __glScissorState;
typedef struct __glHintStateRec __glHintState;
typedef struct __glAccumStateRec __glAccumState;
typedef struct __glFogStateRec __glFogState;
typedef struct __glLineStateRec __glLineState;
typedef struct __glPointStateRec __glPointState;
typedef struct __glAlphaStateRec __glAlphaState;
typedef struct __glOptimizationStateRec __glOptimizationState;
typedef struct __glCurrentState2Rec __glCurrentState2;
typedef struct __glPixelMapHeadRec __glPixelMapHead;
typedef struct __glPixelTransferModeRec __glPixelTransferMode;
typedef struct __glPixelPackModeRec __glPixelPackMode;
typedef struct __glPixelUnpackModeRec __glPixelUnpackMode;
typedef struct __glPixelRec __glPixel;
typedef struct __glPixelStateRec __glPixelState;
typedef struct __glEvaluatorGridRec __glEvaluatorGrid;
typedef struct __glEvaluatorStateRec __glEvaluatorState;
typedef struct __glListStateRec __glListState;
typedef struct __glVertArrayStateRec __glVertArrayState;
typedef struct __glTextureLevelRec __glTextureLevel;
typedef struct __glTextureRec __glTexture;
typedef struct __glTextureState2Rec __glTextureState2;
typedef struct rasStateRec rasState;
typedef struct __glViewportMachineRec __glViewportMachine;
typedef struct matrix4x4Rec matrix4x4;
typedef struct __glMatrixSIMDRec __glMatrixSIMD;
typedef struct __glLightSourceMachineRec __glLightSourceMachine;
typedef struct __glMaterialMachineRec __glMaterialMachine;
typedef struct __glLightMachineRec __glLightMachine;
typedef struct __glDriverProcsRec __glDriverProcs;
typedef struct __glClipRectRec __glClipRect;
typedef struct __glClipInfoStructRec __glClipInfoStruct;
typedef struct __glHashMapBucketRec __glHashMapBucket;
typedef struct __glHashMapRec __glHashMap;
typedef struct __glFragmentRec __glFragment;
typedef struct __glBitmapRec __glBitmap;
typedef struct __glShadeRec __glShade;
typedef struct __glMethodsRec __glMethods;
typedef struct __glAttributeRec __glAttribute;
typedef struct __glClientAttributeRec __glClientAttribute;
typedef struct __glAttributeMachineRec __glAttributeMachine;
typedef struct __glVertexMachineRec __glVertexMachine;
typedef struct __glEvaluator1Rec __glEvaluator1;
typedef struct __glEvaluator2Rec __glEvaluator2;
typedef struct __glEvaluatorMachineRec __glEvaluatorMachine;
typedef struct __glMatrixRec __glMatrix;
typedef struct __glTransformRec __glTransform;
typedef struct __glTransformMachineRec __glTransformMachine;
typedef struct __glListAllocationRec __glListAllocation;
typedef struct __glListItemRec __glListItem;
typedef struct __glListRec __glList;
typedef struct __glListMachineSharedRec __glListMachineShared;
typedef struct __glListMachineRec __glListMachine;
typedef struct __glFeedbackMachineRec __glFeedbackMachine;
typedef struct __glLineMachineRec __glLineMachine;
typedef struct __glProcTableRec __glProcTable;
typedef struct __glSelectMachineRec __glSelectMachine;
typedef struct __glVertexArrayMachineRec __glVertexArrayMachine;
typedef struct __glSoftwareScanlineProcsRec __glSoftwareScanlineProcs;
typedef struct __glValidMachineRec __glValidMachine;
typedef struct __glBufferMachineRec __glBufferMachine;
typedef struct __glSoftwareMachineRec __glSoftwareMachine;
typedef struct __glPrimitiveMachineRec __glPrimitiveMachine;
typedef struct __glSIMDVertexRec __glSIMDVertex;
typedef struct __glTextureMachineRec __glTextureMachine;
typedef struct __glVerticesMachineRec __glVerticesMachine;
typedef struct __glInfoRec __glInfo;
typedef struct __glWindowStateRec __glWindowState;
typedef struct __glContextRec __glContext;


struct __glCoordRec                             // 0x0010 
{
	float                X;                             // 0x0000 
	float                Y;                             // 0x0004 
	float                Z;                             // 0x0008 
	float                W;                             // 0x000c 
}; 

struct __glColorRec                             // 0x0010 
{
	float                R;                             // 0x0000 
	float                G;                             // 0x0004 
	float                B;                             // 0x0008 
	float                A;                             // 0x000c 
}; 

struct __glMaterialStateRec                     // 0x0144  NA 
{
	__glColor            Ambient;                       // 0x0000 
	__glColor            Diffuse;                       // 0x0010 
	__glColor            Specular;                      // 0x0020 
	__glColor            Emissive;                      // 0x0030 
	float                SpecExp;                       // 0x0040 
	unsigned char        SpecExpTable[0x0100];          // 0x0044 
}; 

struct __glPerLightStateRec                     // 0x0078  NA 
{
	char                 Enabled;                       // 0x0000 
	char                 _padding_001[3]; 
	__glColor            Ambient;                       // 0x0004 
	__glColor            Diffuse;                       // 0x0014 
	__glColor            Specular;                      // 0x0024 
	__glCoord            Position;                      // 0x0034 
	__glCoord            PositionEye;                   // 0x0044 
	__glCoord            Direction;                     // 0x0054 
	float                Exponent;                      // 0x0064 
	float                CutOffAngle;                   // 0x0068 
	float                ConstantAttenuation;           // 0x006c 
	float                LinearAttenuation;             // 0x0070 
	float                QuadraticAttenuation;          // 0x0074 
}; 

struct __glLightStateRec                        // 0x066c 
{
	char                 LightingEnabled;               // 0x0000  NA 
	char                 ColorMaterialEnabled;          // 0x0001  NA 
	char                 _padding_002[2]; 
	int                  ColorMaterialFace;             // 0x0004  NA 
	int                  ColorMaterialParam;            // 0x0008  NA 
	int                  ShadingModel;                  // 0x000c  R		Flat or smooth triangle shading 
	__glColor            AmbientLightColor;             // 0x0010  NA 
	char                 LocalViewerEnabled;            // 0x0020  NA 
	char                 TwoSidedEnabled;               // 0x0021  R		If enabled you may see back side triangles 
	char                 _padding_022[2]; 
	__glMaterialState    material[0x0002];              // 0x0024  NA	Front & Back 
	__glPerLightState    light[0x0008];                 // 0x02ac  NA 
}; 

struct __glPolygonStateRec                      // 0x0024  NA 
{
	int                  FrontFaceDirection;            // 0x0000  R		Winding direction for the fron of a triangle.  GL_CW or GL_CCW 
	int                  FrontMode;                     // 0x0004  R		Drawing mode for the front of a triangle.  GL_FILL, GL_LINE, GL_POINT 
	int                  BackMode;                      // 0x0008  R		Drawing mode for the back of a triangle.  GL_FILL, GL_LINE, GL_POINT 
	int                  Cull;                          // 0x000c  R		Culling mode.  GL_FRONT, GL_BACK, GL_FRON_AND_BACK 
	float                OffsetFactor;                  // 0x0010  R		Polygon offset factor 
	float                OffsetUnit;                    // 0x0014  R		Polygon offset unit 
	float                OffsetR;                       // 0x0018  NA 
	char                 CullFaceEnabled;               // 0x001c  R		Culling enable.  Note: culling is done in software and is not necessary in the driver 
	char                 SmoothEnabled;                 // 0x001d  R		Polygon anti-aliasing enable 
	char                 OffsetPointEnabled;            // 0x001e  R		Polygon Offset for Point mode enable 
	char                 OffsetLineEnabled;             // 0x001f  R		Polygon Offset for Line mode enable 
	char                 OffsetFillEnabled;             // 0x0020  R		Polygon Offset for Fill mode enable 
	char                 StippleEnabled;                // 0x0021  R		Polygon stipple enable 
	char                 _padding_022[2]; 
}; 

struct __glDepthStateRec                        // 0x0010 
{
	char                 TestEnabled;                   // 0x0000  R		Depth test enable 
	char                 _padding_001[3]; 
	int                  TestFunction;                  // 0x0004  R		Depth test function 
	float                ClearValue;                    // 0x0008  R		Depth buffer clear value 
	char                 WriteEnabled;                  // 0x000c  R		Depth test write enable 
	char                 _padding_00d[3]; 
}; 

struct __glColorStateRec                        // 0x0028 
{
	char                 RedWriteEnabled;               // 0x0000  R		Red Component write enable 
	char                 GreenWriteEnabled;             // 0x0001  R		Green Component write enable 
	char                 BlueWriteEnabled;              // 0x0002  R		Blue Component write enable 
	char                 AlphaWriteEnabled;             // 0x0003  R		Alpha Component write enable 
	__glColor            ClearValue;                    // 0x0004  R		Color buffer clear value 
	char                 BlendEnabled;                  // 0x0014  R		Color blending enable 
	char                 _padding_015[3]; 
	int                  BlendSrcFunction;              // 0x0018  R		Color blending source function 
	int                  BlendDestFunction;             // 0x001c  R		Color blending destination function 
	int                  LogicOp;                       // 0x0020  R		Color buffer logical operation 
	char                 LogicOpEnabled;                // 0x0024  R		Logical operation enable 
	char                 DitherEnabled;                 // 0x0025  R		Dithering enable 
	char                 _padding_026[2]; 
}; 

struct __glStencilStateRec                      // 0x0024 
{
	char                 TestEnabled;                   // 0x0000  R		Stencil test enabled 
	char                 _padding_001[3]; 
	unsigned int         ClearValue;                    // 0x0004  R		Stencil clear value 
	unsigned int         WriteMask;                     // 0x0008  R		Stencil write mask 
	int                  Function;                      // 0x000c  R		Stencil function 
	unsigned int         Refrence;                      // 0x0010  R		Stencil refrence value 
	unsigned int         FunctionMask;                  // 0x0014  R		Stencil function mask 
	int                  FailOp;                        // 0x0018  R		Stencil Fail Operation 
	int                  DepthFailOp;                   // 0x001c  R		Stencil depth test fail operation 
	int                  DepthPassOp;                   // 0x0020  R		Stencil depth test pass operation 
}; 

struct __glTextureCoordStateRec                 // 0x0024 
{
	int                  mode;                          // 0x0000  NA	How coordinates are being generated 
	__glCoord            eyePlaneEquation;              // 0x0004  NA	Eye plane equation (used if mode == GL_EYE_LINEAR) 
	__glCoord            objectPlaneEquation;           // 0x0014  NA	Object plane equation (used if mode == GL_OBJECT_LINEAR) 
}; 

struct __glXformStateRec                        // 0x006c  NA, Will be used for T&L 
{
	char                 Normalize;                     // 0x0000 
	char                 _padding_001[3]; 
	unsigned int         ClipPlanesMask;                // 0x0004 
	int                  MatrixMode;                    // 0x0008 
	__glCoord            EyeClipPlanes[0x0006];         // 0x000c 
}; 

struct __glViewportStateRec                     // 0x0018  NA, Will be used for T&L 
{
	unsigned int         X;                             // 0x0000 
	unsigned int         Y;                             // 0x0004 
	unsigned int         Width;                         // 0x0008 
	unsigned int         Height;                        // 0x000c 
	float                ZNear;                         // 0x0010 
	float                ZFar;                          // 0x0014 
}; 

struct __glScissorStateRec                      // 0x0014 
{
	char                 Enabled;                       // 0x0000  R		Scissors enable 
	char                 _padding_001[3]; 
	int                  X;                             // 0x0004  R		Left of scissor region, inclusive 
	int                  Y;                             // 0x0008  R		Bottom of scissor region, inclusive 
	int                  Width;                         // 0x000c  R		Width of scissor region 
	int                  Height;                        // 0x0010  R		Height of scissor region 
}; 

struct __glHintStateRec                         // 0x0014 
{
	int                  PerspectiveCorrection;         // 0x0000  R 
	int                  PointSmooth;                   // 0x0004  R 
	int                  LineSmooth;                    // 0x0008  R 
	int                  PolygonSmooth;                 // 0x000c  R 
	int                  Fog;                           // 0x0010  R 
}; 

struct __glAccumStateRec                        // 0x0010 
{
	__glColor            ClearColor;                    // 0x0000  R		Accum buffer clear color 
}; 

struct __glFogStateRec                          // 0x0024 
{
	__glColor            Color;                         // 0x0000  R		Fog color 
	char                 Enabled;                       // 0x0010  R		Fogging enabled 
	char                 _padding_011[3]; 
	int                  Mode;                          // 0x0014  R		Fog Mode (linear, exp, exp2) 
	float                Density;                       // 0x0018  R		Fog density 
	float                Start;                         // 0x001c  R		Fog start 
	float                End;                           // 0x0020  R		Fog end 
}; 

struct __glLineStateRec                         // 0x0018 
{
	char                 SmoothEnabled;                 // 0x0000  R		Anti-Alaising 
	char                 _padding_001[3]; 
	float                RequestedWidth;                // 0x0004  R 
	float                SmoothWidth;                   // 0x0008  R 
	int                  AliasedWidth;                  // 0x000c  R 
	char                 StippleEnabled;                // 0x0010  R 
	char                 _padding_011[1]; 
	unsigned short       StippleMask;                   // 0x0012  R 
	int                  StippleRepeat;                 // 0x0014  R 
}; 

struct __glPointStateRec                        // 0x0010 
{
	char                 SmoothEnabled;                 // 0x0000  R		Anti-Alaising 
	char                 _padding_001[3]; 
	float                SizeRequested;                 // 0x0004  R 
	float                SmoothSize;                    // 0x0008  R 
	int                  AliasedSize;                   // 0x000c  R 
}; 

struct __glAlphaStateRec                        // 0x000c 
{
	char                 TestEnabled;                   // 0x0000  R		 
	char                 _padding_001[3]; 
	int                  TestFunction;                  // 0x0004  R 
	float                TestValue;                     // 0x0008  R		Float 0.0 to 1.0 
}; 

struct __glOptimizationStateRec                 // 0x0010 
{
	unsigned char        UseTempColor;                  // 0x0000  NA 
	unsigned char        UseTempTex[0x0004];            // 0x0001  NA 
	unsigned char        UseTempNormal;                 // 0x0005  NA 
	unsigned char        UseTempEdge;                   // 0x0006  NA 
	unsigned char        Tex2[0x0004];                  // 0x0007  R		Per TMU, when set all texture coords R=0, W=1 
	unsigned char        Tex3[0x0004];                  // 0x000b  R		Per TMU, when set all texture coords W=1 
	char                 _padding_00f[1]; 
}; 

struct __glCurrentState2Rec                     // 0x0074  NA 
{
	__glCoord            Normal;                        // 0x0000 
	__glColor            UserColor;                     // 0x0010 
	__glColor            Color;                         // 0x0020 
	__glCoord            Texture1;                      // 0x0030 
	__glCoord            Texture2;                      // 0x0040 
	__glCoord            Texture3;                      // 0x0050 
	__glCoord            Texture4;                      // 0x0060  
	int                  Edge;                          // 0x0070 
}; 

struct __glPixelMapHeadRec                      // 0x0008  NA 
{
	int                  Size;                          // 0x0000 
	void                 *Map;                          // 0x0004 
}; 

struct __glPixelTransferModeRec                 // 0x003c  Read Only 
{
	float                ScaleR;                        // 0x0000 
	float                ScaleG;                        // 0x0004 
	float                ScaleB;                        // 0x0008 
	float                ScaleA;                        // 0x000c 
	float                ScaleD;                        // 0x0010 
	float                BiasR;                         // 0x0014 
	float                BiasG;                         // 0x0018 
	float                BiasB;                         // 0x001c 
	float                BiasA;                         // 0x0020 
	float                BiasD;                         // 0x0024 
	float                ZoomX;                         // 0x0028 
	float                ZoomY;                         // 0x002c 
	int                  IndexShift;                    // 0x0030 
	int                  IndexOffset;                   // 0x0034 
	char                 MapColor;                      // 0x0038 
	char                 MapStencil;                    // 0x0039 
	char                 _padding_03a[2]; 
}; 

struct __glPixelPackModeRec                     // 0x0014  Read Only 
{
	char                 SwapEndian;                    // 0x0000  
	char                 LsbFirst;                      // 0x0001 
	char                 _padding_002[2]; 
	unsigned int         LineLength;                    // 0x0004 
	unsigned int         SkipLines;                     // 0x0008 
	unsigned int         SkipPixels;                    // 0x000c 
	unsigned int         Alignment;                     // 0x0010 
}; 

struct __glPixelUnpackModeRec                   // 0x0014  Read Only 
{
	char                 SwapEndian;                    // 0x0000  
	char                 LsbFirst;                      // 0x0001 
	char                 _padding_002[2]; 
	unsigned int         LineLength;                    // 0x0004 
	unsigned int         SkipLines;                     // 0x0008 
	unsigned int         SkipPixels;                    // 0x000c 
	unsigned int         Alignment;                     // 0x0010 
}; 

struct __glPixelRec                             // 0x0020 
{
	int                  Format;                        // 0x0000  
	float                R;                             // 0x0004 
	float                G;                             // 0x0008 
	float                B;                             // 0x000c 
	float                A;                             // 0x0010 
	float                D;                             // 0x0014 
	int                  Index;                         // 0x0018 
	int                  Fraction;                      // 0x001c 
}; 

struct __glPixelStateRec                        // 0x00bc  R		This structure contains the state needed for the driver to handle packing and unpacking of user pixel data.  Only needed if the driver is doing its own texture management. 
{
	__glPixelTransferMode transferMode;                  // 0x0000  R		 
	__glPixelPackMode    packModes;                     // 0x003c  R 
	__glPixelUnpackMode  unpackModes;                   // 0x0050  R 
	__glPixelMapHead     pixelMap[0x000a];              // 0x0064  R		__GL_N_PIXEL_MAPS 
	int                  ReadBuffer;                    // 0x00b4  R 
	int                  ReadBufferReturn;              // 0x00b8  R 
}; 

struct __glEvaluatorGridRec                     // 0x000c  NA 
{
	float                Start;                         // 0x0000  
	float                Finish;                        // 0x0004 
	int                  N;                             // 0x0008 
}; 

struct __glEvaluatorStateRec                    // 0x0038  NA 
{
	__glEvaluatorGrid    u1;                            // 0x0000 
	__glEvaluatorGrid    u2;                            // 0x000c 
	__glEvaluatorGrid    v2;                            // 0x0018 
	char                 Map1Enabled[0x0009];           // 0x0024  __GL_MAP_RANGE_COUNT 
	char                 Map2Enabled[0x0009];           // 0x002d  __GL_MAP_RANGE_COUNT 
	char                 AutonormalEnabled;             // 0x0036 
	char                 _padding_037[1]; 
}; 

struct __glListStateRec                         // 0x0004  NA 
{
	unsigned int         ListBase;                      // 0x0000 
}; 

struct __glVertArrayStateRec                    // 0x0090  NA 
{
	int                  SelectedTextureUnit;           // 0x0000 
	const char           *VertexPtr;                    // 0x0004  
	int                  VertexSize;                    // 0x0008 
	int                  VertexType;                    // 0x000c 
	int                  VertexStride;                  // 0x0010 
	const char           *NormalPtr;                    // 0x0014 
	int                  NormalType;                    // 0x0018 
	int                  NormalStride;                  // 0x001c 
	const char           *ColorPtr;                     // 0x0020 
	int                  ColorSize;                     // 0x0024 
	int                  ColorType;                     // 0x0028 
	int                  ColorStride;                   // 0x002c 
	const char           *IndexPtr;                     // 0x0030 
	int                  IndexType;                     // 0x0034 
	int                  IndexStride;                   // 0x0038  
	const char           *TexCoordPtr[0x0004];          // 0x003c 
	int                  TexCoordSize[0x0004];          // 0x004c 
	int                  TexCoordType[0x0004];          // 0x005c 
	int                  TexCoordStride[0x0004];        // 0x006c 
	const char           *EdgeFlagPtr;                  // 0x007c 
	int                  EdgeFlagStride;                // 0x0080 
	char                 VertexArrayEnabled;            // 0x0084 
	char                 NormalArrayEnabled;            // 0x0085 
	char                 ColorArrayEnabled;             // 0x0086 
	char                 IndexArrayEnabled;             // 0x0087 
	char                 TexCoordArrayEnabled[0x0004];  // 0x0088 
	char                 EdgeFlagArrayEnabled;          // 0x008c  
	char                 _padding_08d[3]; 
}; 

struct __glTextureLevelRec                      // 0x0058 
{
	int                  requestedFormat;               // 0x0000  R		The format requested by the user. 
	int                  border;                        // 0x0004  R		Border size 
	unsigned char        *data;                         // 0x0008  R		Pointer to the raw data. NULL if the driver took control. 
	int                  width;                         // 0x000c  R		Image dimensions, including border. 
	int                  height;                        // 0x0010  R		Image dimensions, including border. 
	int                  width2;                        // 0x0014  R		Image dimensions, excluding border. 
	int                  height2;                       // 0x0018  R		Image dimensions, excluding border. 
	int                  baseFormat;                    // 0x001c  R		Base internal format.  GL_ALPHA, GL_RGB, ...  Without bit count. 
	int                  internalFormat;                // 0x0020  RW	Internal format (count and ordering of components). 
	int                  internalType;                  // 0x0024  RW	Internal type.  GL 1.2 types. 
	unsigned int         allocationSize;                // 0x0028  R 
	int                  bytesPerTexel;                 // 0x002c  RW 
	int                  sizeR;                         // 0x0030  RW	Bits of Red per component 
	int                  sizeG;                         // 0x0034  RW	Bits of Green per component 
	int                  sizeB;                         // 0x0038  RW	Bits of Blue per component 
	int                  sizeA;                         // 0x003c  RW	Bits of Alpha per component 
	int                  sizeL;                         // 0x0040  RW	Bits of Luminance per component 
	int                  sizeI;                         // 0x0044  RW	Bits of Intensity per component 
	void                 *usr_vp1;                      // 0x0048  RW	User defined pointer, used by driver to store any special info. 
	void                 *usr_vp2;                      // 0x004c  RW	User defined pointer, used by driver to store any special info. 
	unsigned int         usr_i1;                        // 0x0050  RW	User defined int, used by driver to store any special info. 
	unsigned int         usr_i2;                        // 0x0054  RW	User defined int, used by driver to store any special info. 
}; 

struct __glTextureRec                           // 0x0414 
{
	__glColor            borderColor;                   // 0x0000 
	int                  sWrapMode;                     // 0x0010  R		X 
	int                  tWrapMode;                     // 0x0014  R		Y 
	int                  rWrapMode;                     // 0x0018  R		Z 
	int                  minFilter;                     // 0x001c  R		The filter for texture minification. 
	int                  magFilter;                     // 0x0020  R		The filter for texture magnification. 
	unsigned int         name;                          // 0x0024  R		The texture object name 
	float                priority;                      // 0x0028  R		Float 0.0 to 1.0 
	char                 hasMipmaps;                    // 0x002c  R 
	char                 isValid;                       // 0x002d  R		Is it in a valid state 
	char                 _padding_02e[2]; 
	__glTextureLevel     level[0x000b];                 // 0x0030  		RAS_MAX_MIPMAP_LEVEL, The individual mipmaps. 
	int                  activeLevels;                  // 0x03f8  R 
	int                  dim;                           // 0x03fc  R		Dimension of this texture (1, 2, or 3) 
	void                 (*textureFunc)(__glContext *, __glFragment *, GLfloat s, ... ); // 0x0400  NA 
	void                 *usr_vp1;                      // 0x0404  RW	User defined pointer, used by driver to store any special info 
	void                 *usr_vp2;                      // 0x0408  RW	User defined pointer, used by driver to store any special info 
	unsigned int         usr_i1;                        // 0x040c  RW	User defined int, used by driver to store any special info 
	unsigned int         usr_i2;                        // 0x0410  RW	User defined int, used by driver to store any special info 
}; 

struct __glTextureState2Rec                     // 0x0310 
{
	__glTexture          *Bound[0x0004][0x0006];        // 0x0000  R		__GL_NUMBER_OF_TEXTURE_TARGETS * TextureUnits] 
	__glTextureCoordState s[0x0004];                     // 0x0060  R		Texture Gen state per TMU 
	__glTextureCoordState t[0x0004];                     // 0x00f0  R		Texture Gen state per TMU 
	__glTextureCoordState r[0x0004];                     // 0x0180  R		Texture Gen state per TMU 
	__glTextureCoordState q[0x0004];                     // 0x0210  R		Texture Gen state per TMU 
	unsigned int         SelectedUnit;                  // 0x02a0  R		Currently selected texture unit 
	char                 Enabled1D[0x0004];             // 0x02a4  R		Texture 1D Enable state per TMU 
	char                 Enabled2D[0x0004];             // 0x02a8  R		Texture 2D Enable state per TMU 
	char                 Enabled3D[0x0004];             // 0x02ac  R		Texture 3D Enable state per TMU 
	int                  EnvMode[0x0004];               // 0x02b0  R 
	__glColor            EnvColor[0x0004];              // 0x02c0  R 
	char                 GenEnabled[0x0004][0x0004];    // 0x0300  NA	Texture GenEnable[tmu][coord] 
}; 

struct rasStateRec                              // 0x0dc0 
{
	__glPolygonState     poly;                          // 0x0000  
	__glLightState       light;                         // 0x0024 
	__glDepthState       depth;                         // 0x0690 
	__glColorState       color;                         // 0x06a0 
	__glStencilState     stencil;                       // 0x06c8 
	__glTextureState2    texture;                       // 0x06ec 
	__glXformState       xform;                         // 0x09fc 
	__glViewportState    viewport;                      // 0x0a68 
	__glScissorState     scissor;                       // 0x0a80 
	__glHintState        hint;                          // 0x0a94 
	__glAccumState       accum;                         // 0x0aa8 
	__glFogState         fog;                           // 0x0ab8 
	__glLineState        line;                          // 0x0adc 
	__glPointState       point;                         // 0x0af4 
	__glAlphaState       alpha;                         // 0x0b04 
	__glCurrentState2    current;                       // 0x0b10 
	__glPixelState       pixel;                         // 0x0b84 
	__glEvaluatorState   evaluator;                     // 0x0c40 
	__glListState        list;                          // 0x0c78 
	__glVertArrayState   vertexArray;                   // 0x0c7c  
	__glOptimizationState opt;                           // 0x0d0c 
	char                 polyStippleMask[0x0080];       // 0x0d1c  R		Poloygon stipple mask 
	int                  drawBuffer;                    // 0x0d9c  R		Current drawing buffer 
	int                  drawBufferReturn;              // 0x0da0  NA 
	int                  transformClipY0;               // 0x0da4 
	int                  transformClipY1;               // 0x0da8 
	int                  transformClipX0;               // 0x0dac 
	int                  transformClipX1;               // 0x0db0  
	char                 _padding_db4[12]; 
}; 

struct __glViewportMachineRec                   // 0x0070 
{
	float                ScaleX[0x0004];                // 0x0000  R		Scale factor applied after perspective divide.  All four contain same data on PIII otherwize only [0] is valid 
	float                ScaleY[0x0004];                // 0x0010  R		Scale factor applied after perspective divide.  All four contain same data on PIII otherwize only [0] is valid 
	float                ScaleZ[0x0004];                // 0x0020  R		Scale factor applied after perspective divide.  All four contain same data on PIII otherwize only [0] is valid 
	float                CenterX[0x0004];               // 0x0030  R		Offset factor applied after perspective divide.  All four contain same data on PIII otherwize only [0] is valid 
	float                CenterY[0x0004];               // 0x0040  R		Offset factor applied after perspective divide.  All four contain same data on PIII otherwize only [0] is valid 
	float                CenterZ[0x0004];               // 0x0050  R		Offset factor applied after perspective divide.  All four contain same data on PIII otherwize only [0] is valid 
	float                BoundsX1;                      // 0x0060  R		Screenspace lower X bound, inclusive 
	float                BoundsX2;                      // 0x0064  R		Screenspace upper X bound, exclusive 
	float                BoundsY1;                      // 0x0068  R		Screenspace lower Y bound, inclusive 
	float                BoundsY2;                      // 0x006c  R		Screenspace upper Y bound, exclusive 
}; 

struct matrix4x4Rec                             // 0x0040  Currently not used by the driver, Will be used for T&L cards latter 
{
	float                M00;                           // 0x0000  
	float                M01;                           // 0x0004 
	float                M02;                           // 0x0008 
	float                M03;                           // 0x000c 
	float                M10;                           // 0x0010 
	float                M11;                           // 0x0014 
	float                M12;                           // 0x0018 
	float                M13;                           // 0x001c 
	float                M20;                           // 0x0020 
	float                M21;                           // 0x0024 
	float                M22;                           // 0x0028 
	float                M23;                           // 0x002c 
	float                M30;                           // 0x0030 
	float                M31;                           // 0x0034 
	float                M32;                           // 0x0038 
	float                M33;                           // 0x003c  
}; 

struct __glMatrixSIMDRec                        // 0x0100  Currently not used by the driver, Will be used for T&L cards latter 
{
	float                M00[0x0004];                   // 0x0000  
	float                M01[0x0004];                   // 0x0010 
	float                M02[0x0004];                   // 0x0020 
	float                M03[0x0004];                   // 0x0030 
	float                M10[0x0004];                   // 0x0040 
	float                M11[0x0004];                   // 0x0050 
	float                M12[0x0004];                   // 0x0060 
	float                M13[0x0004];                   // 0x0070 
	float                M20[0x0004];                   // 0x0080 
	float                M21[0x0004];                   // 0x0090 
	float                M22[0x0004];                   // 0x00a0 
	float                M23[0x0004];                   // 0x00b0 
	float                M30[0x0004];                   // 0x00c0 
	float                M31[0x0004];                   // 0x00d0 
	float                M32[0x0004];                   // 0x00e0 
	float                M33[0x0004];                   // 0x00f0  
}; 

struct __glLightSourceMachineRec                // 0x0130  Currently not used by the driver, Will be used for T&L cards latter 
{
	float                AmbientR[0x0004];              // 0x0000 
	float                AmbientG[0x0004];              // 0x0010  
	float                AmbientB[0x0004];              // 0x0020 
	float                SpecularR[0x0004];             // 0x0030 
	float                SpecularG[0x0004];             // 0x0040 
	float                SpecularB[0x0004];             // 0x0050 
	float                DiffuseR[0x0004];              // 0x0060 
	float                DiffuseG[0x0004];              // 0x0070 
	float                DiffuseB[0x0004];              // 0x0080 
	float                HatX[0x0004];                  // 0x0090 
	float                HatY[0x0004];                  // 0x00a0 
	float                HatZ[0x0004];                  // 0x00b0 
	float                PpliHatX[0x0004];              // 0x00c0 
	float                PpliHatY[0x0004];              // 0x00d0 
	float                PpliHatZ[0x0004];              // 0x00e0 
	float                ConstantAttenuation;           // 0x00f0 
	float                LinearAttenuation;             // 0x00f4 
	float                QuadraticAttenuation;          // 0x00f8  
	float                SpotLightExponent;             // 0x00fc 
	__glCoord            Position;                      // 0x0100 
	__glCoord            Direction;                     // 0x0110 
	float                CosCutOffAngle;                // 0x0120 
	float                Attenuation;                   // 0x0124 
	int                  List;                          // 0x0128 
	char                 NoSpot;                        // 0x012c  
	char                 _padding_12d[3]; 
}; 

struct __glMaterialMachineRec                   // 0x0010  Currently not used by the driver, Will be used for T&L cards latter 
{
	float                SceneColorR;                   // 0x0000 
	float                SceneColorG;                   // 0x0004 
	float                SceneColorB;                   // 0x0008 
	float                SceneColorA;                   // 0x000c  
}; 

struct __glLightMachineRec                      // 0x09d0  Currently not used by the driver, Will be used for T&L cards latter 
{
	__glLightSourceMachine source[0x0008];                // 0x0000  __GL_NUMBER_OF_LIGHTS 
	__glMaterialMachine  material[0x0002];              // 0x0980 
	__glLightSourceMachine *sources;                      // 0x09a0 
	int                  List[0x0008];                  // 0x09a4 
	int                  NumberActive;                  // 0x09c4 
	int                  UseSlow;                       // 0x09c8 
	char                 _padding_9cc[4]; 
}; 

struct __glDriverProcsRec                       // 0x022c  The proc table used for communication between GL and the driver.  The driver can set these procs at any time within a call to it.  If a drawing proc is nulled then the driver should call callback_ProcChange afterwards. 
{
	void                 (*triangleFillFront)( __glContext *gc ); // 0x0000 
	void                 (*triangleFillFrontOdd3)( __glContext *gc ); // 0x0004 
	void                 (*triangleFillFrontOdd1)( __glContext *gc ); // 0x0008 
	void                 (*triangleFillFrontEven3)( __glContext *gc ); // 0x000c 
	void                 (*triangleFillFrontEven1)( __glContext *gc ); // 0x0010 
	void                 (*triangleFillFrontFan3)( __glContext *gc ); // 0x0014 
	void                 (*triangleFillFrontFan1)( __glContext *gc ); // 0x0018 
	void                 (*triangleFillFrontUnordered)( __glContext *gc, GLuint a, GLuint b, GLuint c ); // 0x001c 
	void                 (*triangleFillBack)( __glContext *gc ); // 0x0020 
	void                 (*triangleFillBackOdd3)( __glContext *gc ); // 0x0024 
	void                 (*triangleFillBackOdd1)( __glContext *gc ); // 0x0028 
	void                 (*triangleFillBackEven3)( __glContext *gc ); // 0x002c 
	void                 (*triangleFillBackEven1)( __glContext *gc ); // 0x0030 
	void                 (*triangleFillBackFan3)( __glContext *gc ); // 0x0034 
	void                 (*triangleFillBackFan1)( __glContext *gc ); // 0x0038 
	void                 (*triangleFillBackUnordered)( __glContext *gc, GLuint a, GLuint b, GLuint c ); // 0x003c 
	void                 (*triangleLineFront)( __glContext *gc ); // 0x0040 
	void                 (*triangleLineFrontOdd3)( __glContext *gc ); // 0x0044 
	void                 (*triangleLineFrontOdd1)( __glContext *gc ); // 0x0048 
	void                 (*triangleLineFrontEven3)( __glContext *gc ); // 0x004c 
	void                 (*triangleLineFrontEven1)( __glContext *gc ); // 0x0050 
	void                 (*triangleLineFrontFan3)( __glContext *gc ); // 0x0054 
	void                 (*triangleLineFrontFan1)( __glContext *gc ); // 0x0058 
	void                 (*triangleLineFrontUnordered)( __glContext *gc, GLuint a, GLuint b, GLuint c ); // 0x005c 
	void                 (*triangleLineBack)( __glContext *gc ); // 0x0060 
	void                 (*triangleLineBackOdd3)( __glContext *gc ); // 0x0064 
	void                 (*triangleLineBackOdd1)( __glContext *gc ); // 0x0068 
	void                 (*triangleLineBackEven3)( __glContext *gc ); // 0x006c 
	void                 (*triangleLineBackEven1)( __glContext *gc ); // 0x0070 
	void                 (*triangleLineBackFan3)( __glContext *gc ); // 0x0074 
	void                 (*triangleLineBackFan1)( __glContext *gc ); // 0x0078 
	void                 (*triangleLineBackUnordered)( __glContext *gc, GLuint a, GLuint b, GLuint c ); // 0x007c 
	void                 (*trianglePointFront)( __glContext *gc ); // 0x0080 
	void                 (*trianglePointFrontOdd3)( __glContext *gc ); // 0x0084 
	void                 (*trianglePointFrontOdd1)( __glContext *gc ); // 0x0088 
	void                 (*trianglePointFrontEven3)( __glContext *gc ); // 0x008c 
	void                 (*trianglePointFrontEven1)( __glContext *gc ); // 0x0090 
	void                 (*trianglePointFrontFan3)( __glContext *gc ); // 0x0094 
	void                 (*trianglePointFrontFan1)( __glContext *gc ); // 0x0098 
	void                 (*trianglePointFrontUnordered)( __glContext *gc, GLuint a, GLuint b, GLuint c ); // 0x009c 
	void                 (*trianglePointBack)( __glContext *gc ); // 0x00a0 
	void                 (*trianglePointBackOdd3)( __glContext *gc ); // 0x00a4 
	void                 (*trianglePointBackOdd1)( __glContext *gc ); // 0x00a8 
	void                 (*trianglePointBackEven3)( __glContext *gc ); // 0x00ac 
	void                 (*trianglePointBackEven1)( __glContext *gc ); // 0x00b0 
	void                 (*trianglePointBackFan3)( __glContext *gc ); // 0x00b4 
	void                 (*trianglePointBackFan1)( __glContext *gc ); // 0x00b8 
	void                 (*trianglePointBackUnordered)( __glContext *gc, GLuint a, GLuint b, GLuint c ); // 0x00bc 
	void                 (*line)( __glContext *gc );    // 0x00c0 
	void                 (*lineLoop)( __glContext *gc ); // 0x00c4 
	void                 (*lineUnordered)( __glContext *gc, GLuint a, GLuint b ); // 0x00c8 
	void                 (*point)( __glContext *gc );   // 0x00cc 
	void                 (*pointUnordered)( __glContext *gc, GLuint a ); // 0x00d0 
	void                 (*depthTestEnable)( __glContext *gc); // 0x00d4 
	void                 (*depthClear)( __glContext *gc); // 0x00d8 
	void                 (*depthFunc)( __glContext *gc); // 0x00dc 
	void                 (*depthMask)( __glContext *gc); // 0x00e0 
	void                 (*setDepthState)( __glContext *gc ); // 0x00e4 
	void                 (*fogEnable)( __glContext *gc ); // 0x00e8 
	void                 (*fogColor)( __glContext *gc ); // 0x00ec 
	void                 (*setFogState )( __glContext *gc ); // 0x00f0 
	void                 (*alphaTestEnable)( __glContext *gc ); // 0x00f4 
	void                 (*alphaFunc)( __glContext *gc ); // 0x00f8 
	void                 (*blendEnable)( __glContext *gc); // 0x00fc 
	void                 (*blendFunc)( __glContext *gc); // 0x0100 
	void                 (*colorClear)( __glContext *gc); // 0x0104 
	void                 (*colorMask)( __glContext *gc ); // 0x0108 
	void                 (*colorDrawBuffer)( __glContext *gc); // 0x010c 
	void                 (*setColorState)( __glContext *gc); // 0x0110 
	void                 (*polyStippleEnable)( __glContext *gc ); // 0x0114 
	void                 (*polyStippleMask)( __glContext *gc ); // 0x0118 
	void                 (*setPolyStippleState)( __glContext *gc ); // 0x011c 
	void                 (*scissorTestEnable)( __glContext *gc ); // 0x0120 
	void                 (*scissorRect)( __glContext *gc ); // 0x0124 
	void                 (*setScissorState)( __glContext *gc ); // 0x0128 
	void                 (*stencilTestEnable)( __glContext *gc); // 0x012c 
	void                 (*stencilMask)( __glContext *gc); // 0x0130 
	void                 (*stencilFunc)( __glContext *gc); // 0x0134 
	void                 (*stencilOp)( __glContext *gc); // 0x0138 
	void                 (*stencilClear)( __glContext *gc); // 0x013c 
	void                 (*setStencilState)( __glContext *gc ); // 0x0140 
	void                 (*textureEnable)( __glContext *gc ); // 0x0144 
	void                 (*textureSWrapMode)( __glContext *gc ); // 0x0148 
	void                 (*textureTWrapMode)( __glContext *gc ); // 0x014c 
	void                 (*textureMinFilter)( __glContext *gc ); // 0x0150 
	void                 (*textureMagFilter)( __glContext *gc ); // 0x0154 
	void                 (*textureBorderColor)( __glContext *gc ); // 0x0158 
	void                 (*textureEnvMode)( __glContext *gc ); // 0x015c 
	void                 (*textureEnvColor)( __glContext *gc ); // 0x0160 
	void                 (*setTextureState)( __glContext *gc ); // 0x0164 
	void                 (*textureSelect)( __glContext *gc ); // 0x0168 
	void                 (*textureDelete)( __glContext *gc, struct __glTextureRec *tex ); // 0x016c 
	int                  (*textureProxyGetType1D)( __glContext *gc, __glTextureLevel *level ); // 0x0170 
	int                  (*textureProxyGetType2D)( __glContext *gc, __glTextureLevel *level ); // 0x0174 
	int                  (*textureProxyGetType3D)( __glContext *gc, __glTextureLevel *level ); // 0x0178 
	int                  (*textureGetType1D)( __glContext *gc, __glTextureLevel *level ); // 0x017c 
	int                  (*textureGetType2D)( __glContext *gc, __glTextureLevel *level ); // 0x0180 
	int                  (*textureGetType3D)( __glContext *gc, __glTextureLevel *level ); // 0x0184 
	void                 (*textureImage1D)( __glContext *gc, GLint level, const void *data ); // 0x0188 
	void                 (*textureImage2D)( __glContext *gc, GLint level, const void *data ); // 0x018c 
	void                 (*textureImage3D)( __glContext *gc, GLint level, const void *data ); // 0x0190 
	void                 (*textureSubImage1D) (__glContext *gc, GLint level, GLint xoffset, GLsizei w, const void *data); // 0x0194 
	void                 (*textureSubImage2D) (__glContext *gc, GLint level, GLint xoffset, GLint yoffset, GLsizei w, GLsizei h, const void *data); // 0x0198 
	void                 (*textureSubImage3D) (__glContext *gc, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei w, GLsizei h, GLsizei d, const void *data); // 0x019c 
	void                 (*textureExtractPixel1D) (__glContext *gc, GLint level, GLint s, __glPixel *p ); // 0x01a0 
	void                 (*textureExtractPixel2D) (__glContext *gc, GLint level, GLint s, GLint t, __glPixel *p ); // 0x01a4 
	void                 (*textureExtractPixel3D) (__glContext *gc, GLint level, GLint s, GLint t, GLint r, __glPixel *p ); // 0x01a8 
	int                  (*textureIsResident)(__glContext *gc); // 0x01ac 
	void                 (*shutdown)( __glContext *gc ); // 0x01b0 
	void                 (*viewportCreate)( __glContext *gc ); // 0x01b4 
	void                 (*viewportDestroy)( __glContext *gc ); // 0x01b8 
	void                 (*bufferClear)( __glContext *gc, GLuint bits); // 0x01bc 
	void                 (*bufferSwap)( __glContext *gc, GLint useVSync ); // 0x01c0 
	void                 (*bufferLock)( __glContext *gc ); // 0x01c4 
	void                 (*bufferUnlock)( __glContext *gc ); // 0x01c8 
	void                 (*bufferLoadScanline)( __glContext *gc, GLuint bits, GLint x1, GLint x2 ); // 0x01cc 
	void                 (*bufferStoreScanline)( __glContext *gc, GLuint bits, GLint x1, GLint x2 ); // 0x01d0 
	int                  (*bufferVerifyMode)(__glContext *gc, GLint width, GLint height ); // 0x01d4 
	void                 (*flush)( __glContext *gc);    // 0x01d8 
	void                 (*finish)( __glContext *gc);   // 0x01dc 
	void                 (*polySmoothEnabled)( __glContext *gc); // 0x01e0 
	void                 (*polyOffset)( __glContext *gc); // 0x01e4 
	void                 (*polyOffsetFillEnable)( __glContext *gc); // 0x01e8 
	void                 (*polyOffsetLineEnable)( __glContext *gc); // 0x01ec 
	void                 (*polyOffsetPointEnable)( __glContext *gc); // 0x01f0 
	void                 (*SetPolyState)( __glContext *gc ); // 0x01f4 
	void                 (*SetLineWidth)( __glContext *gc ); // 0x01f8 
	void                 (*SetPointSize)( __glContext *gc ); // 0x01fc 
	void                 (*resetRasterProcs)( __glContext *gc ); // 0x0200 
	void                 (*setShadeMode)( __glContext *gc ); // 0x0204 
	float                (*roundZValue)( __glContext *gc, GLfloat Z ); // 0x0208 
	void                 (*abort)( __glContext *gc);    // 0x020c  Called to abort any rendering in progress.  Engine should be idle before returning. 
	void                 (*lockClipList)( __glContext *gc); // 0x0210 
	void                 (*unlockClipList)( __glContext *gc); // 0x0214 
	void                 (*processThreadEvent)(__glContext *gc); // 0x0218  Called as a result of releasing the thread sem.  Can potentially be called more often. 
	void                 (*callback_StoreFrontScanline) (__glContext *gc, GLint x1, GLint x2); // 0x021c  R	Callback for storing the front scanline if the driver cannot copy the front buffer to the frame buffer for some reason. 
	void                 (*callback_ProcChange)(__glContext *gc); // 0x0220  R		Callback for the driver to notify GL that one or more of the drawing procs  
	float                (*callback_GetOffsetBias)(__glContext *gc, GLuint a, GLuint b, GLuint c ); // 0x0224  R Callback to calculate the offset for a triangle.  Figured for 32bit float Z buffer using range 0 to 1 
	void                 (*callback_Perform)(__glContext *gc, GLuint command, void *data ); // 0x0228  R Callback to cause libGL2 to perform one or more tasks.  See the defines. 
}; 

struct __glClipRectRec                          // 0x0010 
{
	int                  Left;                          // 0x0000  
	int                  Top;                           // 0x0004 
	int                  Right;                         // 0x0008 
	int                  Bottom;                        // 0x000c 
}; 

struct __glClipInfoStructRec                    // 0x003c  Clone of the DirectWindow structure.  Treat as Read-Only. Simplified for ASM. 
{
	int                  LocX;                          // 0x0000  R		Location of the left edge of the front buffer (in Be Screen coordinates) 
	int                  LocY;                          // 0x0004  R		Location of the top edge of the front buffer (in Be Screen coordinates) 
	char                 connected;                     // 0x0008  R		Flag indicating if the front buffer is currently enabled for HW acceleration 
	char                 bDirectFormat;                 // 0x0009  R 
	char                 _padding_00a[2]; 
	unsigned char        *frameBuffer;                  // 0x000c  R 
	int                  bytes_per_row;                 // 0x0010  R 
	int                  bits_per_pixel;                // 0x0014  R 
	int                  width;                         // 0x0018  R 
	int                  height;                        // 0x001c  R 
	unsigned int         clip_count;                    // 0x0020  R		Number of clip rects 
	unsigned int         clips_allocated;               // 0x0024  NA	 
	unsigned int         pixel_format;                  // 0x0028  NA 
	__glClipRect         crl;                           // 0x002c  R		Clip rect list.  Note this is overallocated beyond the end of the structure as necessary. 
}; 

struct __glHashMapBucketRec                     // 0x0038 
{
	void                 *ptrs[0x0006];                 // 0x0000  __GL_BUCKET_SIZE 
	unsigned int         keys[0x0006];                  // 0x0018  __GL_BUCKET_SIZE 
	__glHashMapBucket    *previous;                     // 0x0030 
	__glHashMapBucket    *next;                         // 0x0034 
}; 

struct __glHashMapRec                           // 0x41a0 
{
	__glHashMapBucket    baseBuckets[0x012c];           // 0x0000  __GL_BUCKET_COUNT 
}; 

struct __glFragmentRec                          // 0x002c 
{
	__glColor            color;                         // 0x0000 
	int                  x;                             // 0x0010 
	int                  y;                             // 0x0014 
	float                z;                             // 0x0018 
	float                s;                             // 0x001c 
	float                t;                             // 0x0020 
	float                qw;                            // 0x0024 
	float                f;                             // 0x0028  
}; 

struct __glBitmapRec                            // 0x0018 
{
	int                  width;                         // 0x0000 
	int                  height;                        // 0x0004 
	float                Xbo;                           // 0x0008 
	float                Ybo;                           // 0x000c 
	float                Xbi;                           // 0x0010 
	float                Ybi;                           // 0x0014  
}; 

struct __glShadeRec                             // 0x00e4 
{
	short                mmxDB;                         // 0x0000 
	short                mmxDG;                         // 0x0002 
	short                mmxDR;                         // 0x0004 
	short                mmxDA;                         // 0x0006 
	float                xLeft;                         // 0x0008 
	float                xRight;                        // 0x000c 
	int                  xLeftFixed;                    // 0x0010  
	int                  xRightFixed;                   // 0x0014 
	float                dxdyLeft;                      // 0x0018 
	float                dxdyRight;                     // 0x001c 
	float                yBottom;                       // 0x0020 
	float                yTop;                          // 0x0024 
	float                dy;                            // 0x0028 
	int                  iyBottom;                      // 0x002c 
	int                  iyTop;                         // 0x0030 
	float                area;                          // 0x0034 
	float                dxAC;                          // 0x0038  
	float                dxBC;                          // 0x003c 
	float                dyAC;                          // 0x0040 
	float                dyBC;                          // 0x0044 
	int                  dxdyLeftFixed;                 // 0x0048 
	int                  dxdyRightFixed;                // 0x004c 
	float                r0;                            // 0x0050 
	float                g0;                            // 0x0054 
	float                b0;                            // 0x0058 
	float                a0;                            // 0x005c 
	float                drdx;                          // 0x0060 
	float                dgdx;                          // 0x0064  
	float                dbdx;                          // 0x0068 
	float                dadx;                          // 0x006c 
	float                drdy;                          // 0x0070 
	float                dgdy;                          // 0x0074 
	float                dbdy;                          // 0x0078 
	float                dady;                          // 0x007c 
	float                drdxdy;                        // 0x0080 
	float                dgdxdy;                        // 0x0084 
	float                dbdxdy;                        // 0x0088 
	float                dadxdy;                        // 0x008c  
	float                z0;                            // 0x0090 
	float                dzdy;                          // 0x0094 
	float                dzdx;                          // 0x0098 
	float                dzdxdy;                        // 0x009c 
	float                s0;                            // 0x00a0 
	float                t0;                            // 0x00a4 
	float                qw0;                           // 0x00a8 
	float                dsdx;                          // 0x00ac 
	float                dtdx;                          // 0x00b0 
	float                dqwdx;                         // 0x00b4 
	float                dsdy;                          // 0x00b8 
	float                dtdy;                          // 0x00bc 
	float                dqwdy;                         // 0x00c0 
	float                dsdxdy;                        // 0x00c4 
	float                dtdxdy;                        // 0x00c8 
	float                dqwdxdy;                       // 0x00cc 	 
	float                f0;                            // 0x00d0 
	float                dfdy;                          // 0x00d4 
	float                dfdx;                          // 0x00d8 
	float                dfdxdy;                        // 0x00dc  
	char                 ccw;                           // 0x00e0 
	char                 _padding_0e1[3]; 
}; 

struct __glMethodsRec                           // 0x0024 
{
	void                 (*ec1)(__glContext *gc, GLfloat u); // 0x0000 
	void                 (*ec2)(__glContext *gc, GLfloat u, GLfloat v); // 0x0004 
	void                 (*matValidate)(__glContext *gc); // 0x0008 
	void                 (*bitmap)(__glContext *gc, GLint width, GLint height, GLfloat xOrig, GLfloat yOrig, GLfloat xMove, GLfloat yMove, const GLubyte bits[]); // 0x000c 
	void                 (*renderBitmap)(__glContext *gc, __glBitmap *bitmap, GLubyte *bits); // 0x0010 
	void                 (*lineClipParam)();            // 0x0014 
	void                 (*readPixels)(__glContext *gc, GLint x, GLint y, GLint width, GLint height, GLenum format, GLenum type, GLubyte pixels[]); // 0x0018 
	void                 (*fogPoint)(__glContext *gc, __glFragment *frag, GLfloat eyeZ); // 0x001c 
	void                 (*error)(__glContext *gc, GLenum code); // 0x0020 
}; 

struct __glAttributeRec                         // 0x0dd0 
{
	unsigned int         mask;                          // 0x0000  
	char                 _padding_004[12]; 
	rasState             state;                         // 0x0010  
}; 

struct __glClientAttributeRec                   // 0x0150 
{
	unsigned int         mask;                          // 0x0000 
	__glPixelState       pixel;                         // 0x0004 
	__glVertArrayState   vertexArray;                   // 0x00c0  
}; 

struct __glAttributeMachineRec                  // 0x0088 
{
	__glAttribute        *stack[0x0010];                // 0x0000  __GL_ATTRIB_STACK_DEPTH 
	__glClientAttribute  *clientStack[0x0010];          // 0x0040  __GL_CLIENT_ATTRIB_STACK_DEPTH 
	__glAttribute        **stackPointer;                // 0x0080 
	__glClientAttribute  **clientStackPointer;          // 0x0084 
}; 

struct __glVertexMachineRec                     // 0x00dc 
{
	unsigned int         MaterialNeeds;                 // 0x0000 
	void                 (*TransformGroupCurrent)( __glContext *gc ); // 0x0004 
	void                 (*TransformGroup[2])( __glContext *gc ); // 0x0008 
	unsigned int         TransformerCacheAge[0x0010];   // 0x0010  VAPI_CACHE_SIZE 
	unsigned int         TransformerCacheCode[0x0010];  // 0x0050  VAPI_CACHE_SIZE 
	void                 *TransformerCacheGroup[0x0010]; // 0x0090  VAPI_CACHE_SIZE, Transform code. For glEnd. 
	unsigned int         VapiNeeds;                     // 0x00d0 
	unsigned int         XformNeeds;                    // 0x00d4 
	void                 *CacheAllocation;              // 0x00d8  
}; 

struct __glEvaluator1Rec                        // 0x0010 
{
	int                  k;                             // 0x0000 
	int                  order;                         // 0x0004 
	float                u1;                            // 0x0008 
	float                u2;                            // 0x000c  
}; 

struct __glEvaluator2Rec                        // 0x001c 
{
	int                  k;                             // 0x0000 
	int                  majorOrder;                    // 0x0004 
	int                  minorOrder;                    // 0x0008 
	float                u1;                            // 0x000c 
	float                u2;                            // 0x0010 
	float                v1;                            // 0x0014 
	float                v2;                            // 0x0018  
}; 

struct __glEvaluatorMachineRec                  // 0x01d4 
{
	__glEvaluator1       eval1[0x0009];                 // 0x0000  __GL_MAP_RANGE_COUNT 
	__glEvaluator2       eval2[0x0009];                 // 0x0090  __GL_MAP_RANGE_COUNT 
	float                *eval1Data[0x0009];            // 0x018c  __GL_MAP_RANGE_COUNT 
	float                *eval2Data[0x0009];            // 0x01b0  __GL_MAP_RANGE_COUNT 
}; 

struct __glMatrixRec                            // 0x0040 
{
	float                matrix[0x0010];                // 0x0000 
}; 

struct __glTransformRec                         // 0x00c4 
{
	__glMatrix           matrix;                        // 0x0000  
	__glMatrix           inverseTranspose;              // 0x0040 
	__glMatrix           mvp;                           // 0x0080 
	unsigned int         sequence;                      // 0x00c0 
}; 

struct __glTransformMachineRec                  // 0x27e8 
{
	int                  maxWindowDimension;            // 0x0000 
	__glTransform        modelViewStack[0x0020];        // 0x0004  __GL_MODELVIEW_STACK_DEPTH 
	__glTransform        *modelView;                    // 0x1884 
	__glTransform        projectionStack[0x000a];       // 0x1888  __GL_PROJECTION_STACK_DEPTH 
	__glTransform        *projection;                   // 0x2030 
	unsigned int         projectionSequence;            // 0x2034 
	__glTransform        textureStack[0x000a];          // 0x2038  __GL_TEXTURE_STACK_DEPTH 
	__glTransform        *texture;                      // 0x27e0 
	char                 matrixIsIdent;                 // 0x27e4 
	char                 _padding_27e5[3]; 
}; 

struct __glListAllocationRec                    // 0x000c 
{
	__glListAllocation   *next;                         // 0x0000 
	unsigned int         start;                         // 0x0004 
	int                  number;                        // 0x0008  
}; 

struct __glListItemRec                          // 0x0010 
{
	int                  size;                          // 0x0000 
	int                  space;                         // 0x0004 
	int                  data[0x0002];                  // 0x0008  
}; 

struct __glListRec                              // 0x000c 
{
	unsigned int         index;                         // 0x0000 
	__glList             *next;                         // 0x0004 
	__glListItem         *listdata;                     // 0x0008  
}; 

struct __glListMachineSharedRec                 // 0x000c 
{
	__glList             **hashBuckets;                 // 0x0000 
	__glListAllocation   *allocated;                    // 0x0004 
	int                  refcount;                      // 0x0008  
}; 

struct __glListMachineRec                       // 0x0014 
{
	__glListMachineShared *shared;                       // 0x0000 
	__glList             *openList;                     // 0x0004 
	char                 *pc;                           // 0x0008 
	int                  mode;                          // 0x000c 
	int                  nesting;                       // 0x0010  
}; 

struct __glFeedbackMachineRec                   // 0x0014 
{
	char                 overFlowed;                    // 0x0000 
	char                 _padding_001[3]; 
	float                *resultBase;                   // 0x0004 
	float                *result;                       // 0x0008 
	int                  resultLength;                  // 0x000c 
	int                  type;                          // 0x0010  
}; 

struct __glLineMachineRec                       // 0x0008 
{
	int                  stipplePosition;               // 0x0000 
	int                  repeat;                        // 0x0004 
}; 

struct __glProcTableRec                         // 0x0344 
{
	void                 (*Color3bv)(__glContext *, const GLbyte *); // 0x0000 
	void                 (*Color3dv)(__glContext *, const GLdouble *); // 0x0004 
	void                 (*Color3fv)(__glContext *, const GLfloat *); // 0x0008 
	void                 (*Color3iv)(__glContext *, const GLint *); // 0x000c 
	void                 (*Color3sv)(__glContext *, const GLshort *); // 0x0010 
	void                 (*Color3ubv)(__glContext *, const GLubyte *); // 0x0014 
	void                 (*Color3uiv)(__glContext *, const GLuint *); // 0x0018 
	void                 (*Color3usv)(__glContext *, const GLushort *); // 0x001c 
	void                 (*Color4bv)(__glContext *, const GLbyte *); // 0x0020 
	void                 (*Color4dv)(__glContext *, const GLdouble *); // 0x0024 
	void                 (*Color4fv)(__glContext *, const GLfloat *); // 0x0028 
	void                 (*Color4iv)(__glContext *, const GLint *); // 0x002c 
	void                 (*Color4sv)(__glContext *, const GLshort *); // 0x0030 
	void                 (*Color4ubv)(__glContext *, const GLubyte *); // 0x0034 
	void                 (*Color4uiv)(__glContext *, const GLuint *); // 0x0038 
	void                 (*Color4usv)(__glContext *, const GLushort *); // 0x003c 
	void                 (*Normal3fv)(const GLfloat *); // 0x0040 
	void                 (*TexCoord1fv)(const GLfloat *); // 0x0044 
	void                 (*TexCoord2fv)(const GLfloat *); // 0x0048 
	void                 (*TexCoord3fv)(const GLfloat *); // 0x004c 
	void                 (*TexCoord4fv)(const GLfloat *); // 0x0050 
	void                 (*Vertex2fv)(const GLfloat *); // 0x0054 
	void                 (*Vertex3fv)(const GLfloat *); // 0x0058 
	void                 (*Vertex4fv)(const GLfloat *); // 0x005c 
	void                 (*Begin)(GLenum);              // 0x0060 
	void                 (*End)();                      // 0x0064 
	void                 (*CallList)( __glContext *, GLuint); // 0x0068 
	void                 (*CallLists)( __glContext *, GLsizei, GLenum, const void *); // 0x006c 
	void                 (*ListBase)( __glContext *, GLuint); // 0x0070 
	void                 (*Bitmap)( __glContext *, GLsizei, GLsizei, GLfloat, GLfloat, GLfloat, GLfloat, const GLubyte *); // 0x0074 
	void                 (*EdgeFlag)( __glContext *, GLboolean); // 0x0078 
	void                 (*EdgeFlagv)( __glContext *, const GLboolean *); // 0x007c 
	void                 (*Indexd)( __glContext *, GLdouble); // 0x0080 
	void                 (*Indexdv)( __glContext *, const GLdouble *); // 0x0084 
	void                 (*Indexf)( __glContext *, GLfloat); // 0x0088 
	void                 (*Indexfv)( __glContext *, const GLfloat *); // 0x008c 
	void                 (*Indexi)( __glContext *, GLint); // 0x0090 
	void                 (*Indexiv)( __glContext *, const GLint *); // 0x0094 
	void                 (*Indexs)( __glContext *, GLshort); // 0x0098 
	void                 (*Indexsv)( __glContext *, const GLshort *); // 0x009c 
	void                 (*Indexub)( __glContext *, GLubyte); // 0x00a0 
	void                 (*Indexubv)( __glContext *, const GLubyte *); // 0x00a4 
	void                 (*RasterPos2d)( __glContext *, GLdouble, GLdouble); // 0x00a8 
	void                 (*RasterPos2dv)( __glContext *, const GLdouble *); // 0x00ac 
	void                 (*RasterPos2f)( __glContext *, GLfloat, GLfloat); // 0x00b0 
	void                 (*RasterPos2fv)( __glContext *, const GLfloat *); // 0x00b4 
	void                 (*RasterPos2i)( __glContext *, GLint, GLint); // 0x00b8 
	void                 (*RasterPos2iv)( __glContext *, const GLint *); // 0x00bc 
	void                 (*RasterPos2s)( __glContext *, GLshort, GLshort); // 0x00c0 
	void                 (*RasterPos2sv)( __glContext *, const GLshort *); // 0x00c4 
	void                 (*RasterPos3d)( __glContext *, GLdouble, GLdouble, GLdouble); // 0x00c8 
	void                 (*RasterPos3dv)( __glContext *, const GLdouble *); // 0x00cc 
	void                 (*RasterPos3f)( __glContext *, GLfloat, GLfloat, GLfloat); // 0x00d0 
	void                 (*RasterPos3fv)( __glContext *, const GLfloat *); // 0x00d4 
	void                 (*RasterPos3i)( __glContext *, GLint, GLint, GLint); // 0x00d8 
	void                 (*RasterPos3iv)( __glContext *, const GLint *); // 0x00dc 
	void                 (*RasterPos3s)( __glContext *, GLshort, GLshort, GLshort); // 0x00e0 
	void                 (*RasterPos3sv)( __glContext *, const GLshort *); // 0x00e4 
	void                 (*RasterPos4d)( __glContext *, GLdouble, GLdouble, GLdouble, GLdouble); // 0x00e8 
	void                 (*RasterPos4dv)( __glContext *, const GLdouble *); // 0x00ec 
	void                 (*RasterPos4f)( __glContext *, GLfloat, GLfloat, GLfloat, GLfloat); // 0x00f0 
	void                 (*RasterPos4fv)( __glContext *, const GLfloat *); // 0x00f4 
	void                 (*RasterPos4i)( __glContext *, GLint, GLint, GLint, GLint); // 0x00f8 
	void                 (*RasterPos4iv)( __glContext *, const GLint *); // 0x00fc 
	void                 (*RasterPos4s)( __glContext *, GLshort, GLshort, GLshort, GLshort); // 0x0100 
	void                 (*RasterPos4sv)( __glContext *, const GLshort *); // 0x0104 
	void                 (*Rectd)( __glContext *, GLdouble, GLdouble, GLdouble, GLdouble); // 0x0108 
	void                 (*Rectdv)( __glContext *, const GLdouble *, const GLdouble *); // 0x010c 
	void                 (*Rectf)( __glContext *, GLfloat, GLfloat, GLfloat, GLfloat); // 0x0110 
	void                 (*Rectfv)( __glContext *, const GLfloat *, const GLfloat *); // 0x0114 
	void                 (*Recti)( __glContext *, GLint, GLint, GLint, GLint); // 0x0118 
	void                 (*Rectiv)( __glContext *, const GLint *, const GLint *); // 0x011c 
	void                 (*Rects)( __glContext *, GLshort, GLshort, GLshort, GLshort); // 0x0120 
	void                 (*Rectsv)( __glContext *, const GLshort *, const GLshort *); // 0x0124 
	void                 (*ClipPlane)( __glContext *, GLenum, const GLdouble *); // 0x0128 
	void                 (*ColorMaterial)( __glContext *, GLenum, GLenum); // 0x012c 
	void                 (*CullFace)( __glContext *, GLenum); // 0x0130 
	void                 (*Fogf)( __glContext *, GLenum, GLfloat); // 0x0134 
	void                 (*Fogfv)( __glContext *, GLenum, const GLfloat *); // 0x0138 
	void                 (*Fogi)( __glContext *, GLenum, GLint); // 0x013c 
	void                 (*Fogiv)( __glContext *, GLenum, const GLint *); // 0x0140 
	void                 (*FrontFace)( __glContext *, GLenum); // 0x0144 
	void                 (*Hint)( __glContext *, GLenum, GLenum); // 0x0148 
	void                 (*Lightf)( __glContext *, GLenum, GLenum, GLfloat); // 0x014c 
	void                 (*Lightfv)( __glContext *, GLenum, GLenum, const GLfloat *); // 0x0150 
	void                 (*Lighti)( __glContext *, GLenum, GLenum, GLint); // 0x0154 
	void                 (*Lightiv)( __glContext *, GLenum, GLenum, const GLint *); // 0x0158 
	void                 (*LightModelf)( __glContext *, GLenum, GLfloat); // 0x015c 
	void                 (*LightModelfv)( __glContext *, GLenum, const GLfloat *); // 0x0160 
	void                 (*LightModeli)( __glContext *, GLenum, GLint); // 0x0164 
	void                 (*LightModeliv)( __glContext *, GLenum, const GLint *); // 0x0168 
	void                 (*LineStipple)( __glContext *, GLint, GLushort); // 0x016c 
	void                 (*LineWidth)( __glContext *, GLfloat); // 0x0170 
	void                 (*Materialf)( __glContext *, GLenum, GLenum, GLfloat); // 0x0174 
	void                 (*Materialfv)( __glContext *, GLenum, GLenum, const GLfloat *); // 0x0178 
	void                 (*Materiali)( __glContext *, GLenum, GLenum, GLint); // 0x017c 
	void                 (*Materialiv)( __glContext *, GLenum, GLenum, const GLint *); // 0x0180 
	void                 (*PointSize)( __glContext *, GLfloat); // 0x0184 
	void                 (*PolygonMode)( __glContext *, GLenum, GLenum); // 0x0188 
	void                 (*PolygonStipple)( __glContext *, const GLubyte *); // 0x018c 
	void                 (*Scissor)( __glContext *, GLint, GLint, GLsizei, GLsizei); // 0x0190 
	void                 (*ShadeModel)( __glContext *, GLenum); // 0x0194 
	void                 (*TexParameterf)( __glContext *, GLenum, GLenum, GLfloat); // 0x0198 
	void                 (*TexParameterfv)( __glContext *, GLenum, GLenum, const GLfloat *); // 0x019c 
	void                 (*TexParameteri)( __glContext *, GLenum, GLenum, GLint); // 0x01a0 
	void                 (*TexParameteriv)( __glContext *, GLenum, GLenum, const GLint *); // 0x01a4 
	void                 (*TexImage1D)( __glContext *, GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const void *); // 0x01a8 
	void                 (*TexImage2D)( __glContext *, GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *); // 0x01ac 
	void                 (*TexEnvf)( __glContext *, GLenum, GLenum, GLfloat); // 0x01b0 
	void                 (*TexEnvfv)( __glContext *, GLenum, GLenum, const GLfloat *); // 0x01b4 
	void                 (*TexEnvi)( __glContext *, GLenum, GLenum, GLint); // 0x01b8 
	void                 (*TexEnviv)( __glContext *, GLenum, GLenum, const GLint *); // 0x01bc 
	void                 (*TexGend)( __glContext *, GLenum, GLenum, GLdouble); // 0x01c0 
	void                 (*TexGendv)( __glContext *, GLenum, GLenum, const GLdouble *); // 0x01c4 
	void                 (*TexGenf)( __glContext *, GLenum, GLenum, GLfloat); // 0x01c8 
	void                 (*TexGenfv)( __glContext *, GLenum, GLenum, const GLfloat *); // 0x01cc 
	void                 (*TexGeni)( __glContext *, GLenum, GLenum, GLint); // 0x01d0 
	void                 (*TexGeniv)( __glContext *, GLenum, GLenum, const GLint *); // 0x01d4 
	void                 (*InitNames)( __glContext * ); // 0x01d8 
	void                 (*LoadName)( __glContext *, GLuint); // 0x01dc 
	void                 (*PassThrough)( __glContext *, GLfloat); // 0x01e0 
	void                 (*PopName)( __glContext * );   // 0x01e4 
	void                 (*PushName)( __glContext *, GLuint); // 0x01e8 
	void                 (*DrawBuffer)( __glContext *, GLenum); // 0x01ec 
	void                 (*Clear)( __glContext *, GLbitfield); // 0x01f0 
	void                 (*ClearAccum)( __glContext *, GLfloat, GLfloat, GLfloat, GLfloat); // 0x01f4 
	void                 (*ClearIndex)( __glContext *, GLfloat); // 0x01f8 
	void                 (*ClearColor)( __glContext *, GLclampf, GLclampf, GLclampf, GLclampf); // 0x01fc 
	void                 (*ClearStencil)( __glContext *, GLint); // 0x0200 
	void                 (*ClearDepth)( __glContext *, GLclampd); // 0x0204 
	void                 (*StencilMask)( __glContext *, GLuint); // 0x0208 
	void                 (*ColorMask)( __glContext *, GLboolean, GLboolean, GLboolean, GLboolean); // 0x020c 
	void                 (*DepthMask)( __glContext *, GLboolean); // 0x0210 
	void                 (*IndexMask)( __glContext *, GLuint); // 0x0214 
	void                 (*Accum)( __glContext *, GLenum, GLfloat); // 0x0218 
	void                 (*Disable)( __glContext *, GLenum); // 0x021c 
	void                 (*Enable)( __glContext *, GLenum); // 0x0220 
	void                 (*PopAttrib)( __glContext * ); // 0x0224 
	void                 (*PushAttrib)( __glContext *, GLbitfield); // 0x0228 
	void                 (*Map1d)( __glContext *, GLenum, GLdouble, GLdouble, GLint, GLint, const GLdouble *); // 0x022c 
	void                 (*Map1f)( __glContext *, GLenum, GLfloat, GLfloat, GLint, GLint, const GLfloat *); // 0x0230 
	void                 (*Map2d)( __glContext *, GLenum, GLdouble, GLdouble, GLint, GLint, GLdouble, GLdouble, GLint, GLint, const GLdouble *); // 0x0234 
	void                 (*Map2f)( __glContext *, GLenum, GLfloat, GLfloat, GLint, GLint, GLfloat, GLfloat, GLint, GLint, const GLfloat *); // 0x0238 
	void                 (*MapGrid1d)( __glContext *, GLint, GLdouble, GLdouble); // 0x023c 
	void                 (*MapGrid1f)( __glContext *, GLint, GLfloat, GLfloat); // 0x0240 
	void                 (*MapGrid2d)( __glContext *, GLint, GLdouble, GLdouble, GLint, GLdouble, GLdouble); // 0x0244 
	void                 (*MapGrid2f)( __glContext *, GLint, GLfloat, GLfloat, GLint, GLfloat, GLfloat); // 0x0248 
	void                 (*EvalCoord1d)( __glContext *, GLdouble); // 0x024c 
	void                 (*EvalCoord1dv)( __glContext *, const GLdouble *); // 0x0250 
	void                 (*EvalCoord1f)( __glContext *, GLfloat); // 0x0254 
	void                 (*EvalCoord1fv)( __glContext *, const GLfloat *); // 0x0258 
	void                 (*EvalCoord2d)( __glContext *, GLdouble, GLdouble); // 0x025c 
	void                 (*EvalCoord2dv)( __glContext *, const GLdouble *); // 0x0260 
	void                 (*EvalCoord2f)( __glContext *, GLfloat, GLfloat); // 0x0264 
	void                 (*EvalCoord2fv)( __glContext *, const GLfloat *); // 0x0268 
	void                 (*EvalMesh1)( __glContext *, GLenum, GLint, GLint); // 0x026c 
	void                 (*EvalPoint1)( __glContext *, GLint); // 0x0270 
	void                 (*EvalMesh2)( __glContext *, GLenum, GLint, GLint, GLint, GLint); // 0x0274 
	void                 (*EvalPoint2)( __glContext *, GLint, GLint); // 0x0278 
	void                 (*AlphaFunc)( __glContext *, GLenum, GLclampf); // 0x027c 
	void                 (*BlendFunc)( __glContext *, GLenum, GLenum); // 0x0280 
	void                 (*LogicOp)( __glContext *, GLenum); // 0x0284 
	void                 (*StencilFunc)( __glContext *, GLenum, GLint, GLuint); // 0x0288 
	void                 (*StencilOp)( __glContext *, GLenum, GLenum, GLenum); // 0x028c 
	void                 (*DepthFunc)( __glContext *, GLenum); // 0x0290 
	void                 (*PixelZoom)( __glContext *, GLfloat, GLfloat); // 0x0294 
	void                 (*PixelTransferf)( __glContext *, GLenum, GLfloat); // 0x0298 
	void                 (*PixelTransferi)( __glContext *, GLenum, GLint); // 0x029c 
	void                 (*PixelMapfv)( __glContext *, GLenum, GLsizei, const GLfloat *); // 0x02a0 
	void                 (*PixelMapuiv)( __glContext *, GLenum, GLsizei, const GLuint *); // 0x02a4 
	void                 (*PixelMapusv)( __glContext *, GLenum, GLsizei, const GLushort *); // 0x02a8 
	void                 (*ReadBuffer)( __glContext *, GLenum); // 0x02ac 
	void                 (*CopyPixels)( __glContext *, GLint, GLint, GLsizei, GLsizei, GLenum); // 0x02b0 
	void                 (*DrawPixels)( __glContext *, GLsizei, GLsizei, GLenum, GLenum, const void *); // 0x02b4 
	void                 (*DepthRange)( __glContext *, GLclampd, GLclampd); // 0x02b8 
	void                 (*Frustum)( __glContext *, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble); // 0x02bc 
	void                 (*LoadIdentity)( __glContext * ); // 0x02c0 
	void                 (*LoadMatrixf)( __glContext *, const GLfloat *); // 0x02c4 
	void                 (*LoadMatrixd)( __glContext *, const GLdouble *); // 0x02c8 
	void                 (*MatrixMode)( __glContext *, GLenum); // 0x02cc 
	void                 (*MultMatrixf)( __glContext *, const GLfloat *); // 0x02d0 
	void                 (*MultMatrixd)( __glContext *, const GLdouble *); // 0x02d4 
	void                 (*Ortho)( __glContext *, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble); // 0x02d8 
	void                 (*PopMatrix)( __glContext * ); // 0x02dc 
	void                 (*PushMatrix)( __glContext * ); // 0x02e0 
	void                 (*Rotated)( __glContext *, GLdouble, GLdouble, GLdouble, GLdouble); // 0x02e4 
	void                 (*Rotatef)( __glContext *, GLfloat, GLfloat, GLfloat, GLfloat); // 0x02e8 
	void                 (*Scaled)( __glContext *, GLdouble, GLdouble, GLdouble); // 0x02ec 
	void                 (*Scalef)( __glContext *, GLfloat, GLfloat, GLfloat); // 0x02f0 
	void                 (*Translated)( __glContext *, GLdouble, GLdouble, GLdouble); // 0x02f4 
	void                 (*Translatef)( __glContext *, GLfloat, GLfloat, GLfloat); // 0x02f8 
	void                 (*Viewport)( __glContext *, GLint, GLint, GLsizei, GLsizei); // 0x02fc 
	void                 (*PolygonOffset)( __glContext *, GLfloat, GLfloat); // 0x0300 
	void                 (*ArrayElement)( __glContext *, GLint); // 0x0304 
	void                 (*DrawArrays)( __glContext *, GLenum, GLint, GLsizei); // 0x0308 
	void                 (*DrawElements)( __glContext *, GLenum, GLsizei, GLenum, const void *); // 0x030c 
	void                 (*TexSubImage1D)( __glContext *, GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const void *); // 0x0310 
	void                 (*TexSubImage2D)( __glContext *, GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *); // 0x0314 
	void                 (*CopyTexImage1D)( __glContext *, GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint); // 0x0318 
	void                 (*CopyTexImage2D)( __glContext *, GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint); // 0x031c 
	void                 (*CopyTexSubImage1D)( __glContext *, GLenum, GLint, GLint, GLint, GLint, GLsizei); // 0x0320 
	void                 (*CopyTexSubImage2D)( __glContext *, GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei); // 0x0324 
	void                 (*BindTexture)( __glContext *, GLenum, GLuint); // 0x0328 
	void                 (*PrioritizeTextures)( __glContext *, GLsizei, const GLuint *, const GLclampf *); // 0x032c 
	void                 (*MultiTexCoord1fvARB)( GLenum, const float * ); // 0x0330 
	void                 (*MultiTexCoord2fvARB)( GLenum, const float * ); // 0x0334 
	void                 (*MultiTexCoord3fvARB)( GLenum, const float * ); // 0x0338 
	void                 (*MultiTexCoord4fvARB)( GLenum, const float * ); // 0x033c 
	void                 (*ActiveTextureARB)( GLenum ); // 0x0340 
}; 

struct __glSelectMachineRec                     // 0x0220 
{
	char                 hit;                           // 0x0000 
	char                 _padding_001[3]; 
	unsigned long        stack[0x0080];                 // 0x0004  __GL_NAME_STACK_DEPTH 
	unsigned long        *sp;                           // 0x0204 
	char                 overFlowed;                    // 0x0208 
	char                 _padding_209[3]; 
	unsigned long        *resultBase;                   // 0x020c 
	unsigned long        *result;                       // 0x0210 
	long                 resultLength;                  // 0x0214 
	long                 hits;                          // 0x0218 
	unsigned long        *z;                            // 0x021c  
}; 

struct __glVertexArrayMachineRec                // 0x00a0 
{
	void                 (*vertexCall)(const char *);   // 0x0000 
	void                 (*normalCall)(const char *);   // 0x0004 
	void                 (*colorCall)(const char *);    // 0x0008 
	void                 (*indexCall)(const char *);    // 0x000c 
	void                 (*texCoordCall)(const char *); // 0x0010 
	void                 (*edgeFlagCall)(const char *); // 0x0014 
	int                  vertexSkip;                    // 0x0018 
	int                  normalSkip;                    // 0x001c 
	int                  colorSkip;                     // 0x0020 
	int                  indexSkip;                     // 0x0024 
	int                  texCoordSkip[0x0004];          // 0x0028 
	int                  edgeFlagSkip;                  // 0x0038  
	unsigned char        *drawElementCodeCache[0x0008]; // 0x003c  [4096 * 8] 
	unsigned int         drawElementNeeds[0x0008];      // 0x005c 
	unsigned int         drawElementAge[0x0008];        // 0x007c 
	unsigned int         drawElementCurrentNeeds;       // 0x009c 
}; 

struct __glSoftwareScanlineProcsRec             // 0x001c 
{
	void                 (*scanlineDepth)( GLubyte *valid, GLfloat *zbuf, GLfloat z1, GLfloat dz, GLint w ); // 0x0000 
	unsigned int         loadBits;                      // 0x0004 
	unsigned int         storeBits;                     // 0x0008 
	char                 valid;                         // 0x000c 
	char                 maskEnabled;                   // 0x000d 
	char                 colorWriteEnabled;             // 0x000e 
	char                 fastScanline;                  // 0x000f 
	void                 *processorFuncData;            // 0x0010 
	void                 (*processorFunc)(__glContext *, const __glFragment *, __glShade *, GLint w ); // 0x0014 
	unsigned int         processorNeeds;                // 0x0018  
}; 

struct __glValidMachineRec                      // 0x0028 
{
	unsigned int         All;                           // 0x0000 
	unsigned int         ModelMatrix;                   // 0x0004 
	unsigned int         ProjectionMatrix;              // 0x0008 
	unsigned int         VertexProcs;                   // 0x000c 
	unsigned int         LightData;                     // 0x0010 
	unsigned int         PrimProcessor;                 // 0x0014 
	unsigned int         VapiProcessor;                 // 0x0018 
	unsigned int         ModelMatrixType;               // 0x001c 
	unsigned int         ProjectionMatrixType;          // 0x0020 
	unsigned int         MVPMatrixType;                 // 0x0024  
}; 

struct __glBufferMachineRec                     // 0x00b8 
{
	unsigned int         *ScanlineFB;                   // 0x0000  NA	Scanline buffer, holds a color scanline to be written to the HW buffer.  
	unsigned int         *ScanlineFBIN;                 // 0x0004  NA	Scanline buffer, holds a color scanline read from the HW buffer.  
	__glColor            *ScanlineA;                    // 0x0008  NA	Scanline buffer, holds a accumulation buffer scanline read from or to be written to HW. 
	float                *ScanlineZ;                    // 0x000c  NA	Scanline buffer, holds a depth buffer scanline read from or to be written to HW 
	unsigned char        *ScanlineS;                    // 0x0010  NA	Scanline buffer, holds a stencil buffer scanline read from or to be written to HW. 
	unsigned char        *ScanlineV;                    // 0x0014  NA	Scanline Valid buffer, contains 1s for pixels to be written and 0s for not. 
	int                  ScanlineY;                     // 0x0018  R		Scanline buffer, The Y coordinate for the current scanline. 
	int                  Height;                        // 0x001c  R		Height of the front buffer in pixels 
	int                  Width;                         // 0x0020  R		Width of the front buffer in pixels 
	void                 *ColorFront;                   // 0x0024  R		Pointer to the softawre front color buffer if pressent. 
	void                 *ColorBack;                    // 0x0028  R		Pointer to the softawre back color buffer if pressent. 
	void                 *Depth;                        // 0x002c  R		Pointer to the softawre depth buffer if pressent. 
	void                 *Accum;                        // 0x0030  R		Pointer to the softawre accumulation buffer if pressent. 
	void                 *Stencil;                      // 0x0034  R		Pointer to the softawre stencil buffer if pressent. 
	unsigned int         FullScreen;                    // 0x0038  R		Flag to indicate if the application has exclusive access to the screen. 
	unsigned int         ColorFrontHardware;            // 0x003c  RW	Front buffer	1=HW  0=Fallback 
	unsigned int         ColorBackEnabled;              // 0x0040  R 
	unsigned int         ColorBackHardware;             // 0x0044  RW	Back buffer	1=HW  0=Fallback 
	unsigned int         DepthEnabled;                  // 0x0048  R 
	unsigned int         DepthHardware;                 // 0x004c  RW	1=HW  0=Fallback 
	unsigned int         AccumEnabled;                  // 0x0050  R 
	unsigned int         AccumHardware;                 // 0x0054  RW	1=HW  0=Fallback 
	unsigned int         StencilEnabled;                // 0x0058  R		Flag to indicate if the user specified a stencil buffer be created. 
	unsigned int         StencilHardware;               // 0x005c  RW	1=HW  0=Fallback 
	__glColor            ColorScale;                    // 0x0060  RW	Range for colors, 0 to N 
	int                  bitsRed;                       // 0x0070  RW	Set the bit count in AcceleratorInit 
	int                  bitsGreen;                     // 0x0074  RW	Set the bit count in AcceleratorInit 
	int                  bitsBlue;                      // 0x0078  RW	Set the bit count in AcceleratorInit 
	int                  bitsAlpha;                     // 0x007c  RW	Set the bit count in AcceleratorInit 
	int                  bitsDepth;                     // 0x0080  RW	Set the bit count in AcceleratorInit 
	int                  bitsStencil;                   // 0x0084  RW	Set the bit count in AcceleratorInit 
	int                  bitsAccumRed;                  // 0x0088  RW	Set the bit count in AcceleratorInit 
	int                  bitsAccumGreen;                // 0x008c  RW	Set the bit count in AcceleratorInit 
	int                  bitsAccumBlue;                 // 0x0090  RW	Set the bit count in AcceleratorInit 
	int                  bitsAccumAlpha;                // 0x0094  RW	Set the bit count in AcceleratorInit 
	unsigned int         UserColor;                     // 0x0098  R 
	unsigned int         UserDepth;                     // 0x009c  R 
	unsigned int         UserStencil;                   // 0x00a0  R 
	unsigned int         UserAccum;                     // 0x00a4  R 
	unsigned int         RefreshRate;                   // 0x00a8  R		Refresh rate for fullscreen mode 
	float                gammaRed;                      // 0x00ac  R 
	float                gammaGreen;                    // 0x00b0  R 
	float                gammaBlue;                     // 0x00b4  R 
}; 

struct __glSoftwareMachineRec                   // 0x0004 
{
	char                 ProcsCurrent;                  // 0x0000 
	char                 PathColorEnable;               // 0x0001 
	char                 PathDisable;                   // 0x0002 
	char                 _padding_003[1]; 
}; 

struct __glPrimitiveMachineRec                  // 0x021c  The data used for geomitry processing of primitives. 
{
	int                  Count;                         // 0x0000  Records the next primitive vertex to be processed. 
	void                 (*GroupProcessor) ( __glContext *gc ); // 0x0004  Processor for the beginning or middle of primitive processing. 
	void                 (*End) ( __glContext *gc );    // 0x0008  Processor for the end of primitive groups that can handle partial SIMD groups. 
	unsigned int         CacheCurrentNeeds;             // 0x000c  The current needs for primitive processing. 
	void                 *CacheProcess[0x000a];         // 0x0010  The current GroupProcessors for the various primitives. NULL means they need to be looked up or generated. 
	void                 *CacheEnd[0x000a];             // 0x0038  The current Ends for the various primitives. NULL means they need to be looked up or generated. 
	unsigned int         CacheCode[0x0020];             // 0x0060  PRIM_CACHE_SIZE, Needs code for cache entry 
	unsigned int         CacheAge[0x0020];              // 0x00e0  PRIM_CACHE_SIZE, Age of cache entry 
	void                 *CacheProcessPtrs[0x0020];     // 0x0160  PRIM_CACHE_SIZE, Pointer to processing routine past SIMD prefix. 
	void                 *CacheAllocation;              // 0x01e0  Pointer to the allocation of memory for the cache. 
	void                 (*ClippedPolyProcFront) (__glContext *); // 0x01e4  The current unordered triangle proc for front facing triangles. 
	void                 (*ClippedPolyProcBack) (__glContext *); // 0x01e8  The current unordered triangle proc for back facing triangles. 
	int                  EdgeTag;                       // 0x01ec  The current edge tag.  1=Draw edge,  0=Do not draw edge 
	unsigned char        CullAndMask;                   // 0x01f0  0x00 = disabled,  0xff=enabled 
	unsigned char        CullXorMask;                   // 0x01f1  0x01 = GL_BACK, 0x00=GL_FRONT, 0x10=GL_FRONT_AND_BACK 
	unsigned char        CullCurrentFacing;             // 0x01f2 
	unsigned char        FacingXorMask;                 // 0x01f3  0x00 = GL_CCW,  0x01=GL_CW 
	unsigned int         Provoking;                     // 0x01f4  The provoking vertex for flat shading.  Use to select color. 
	unsigned int         CallSize;                      // 0x01f8  The current call point for SIMD vertex processors. 
	int                  FirstVertexInGroup;            // 0x01fc 
	int                  CurrentGroupCount;             // 0x0200 
	int                  CurrentVertex;                 // 0x0204  The vertex that the next call to glVertexNXX will use. 
	int                  StripFlag;                     // 0x0208 
	__glColor            ColorScale;                    // 0x020c  Range for colors, 0 to N 
}; 

struct __glSIMDVertexRec                        // 0x02e0 
{
	float                ObjX[0x0004];                  // 0x0000 
	float                ObjY[0x0004];                  // 0x0010 
	float                ObjZ[0x0004];                  // 0x0020 
	float                ObjW[0x0004];                  // 0x0030 
	float                ClipX[0x0004];                 // 0x0040 
	float                ClipY[0x0004];                 // 0x0050 
	float                ClipZ[0x0004];                 // 0x0060 
	float                ClipW[0x0004];                 // 0x0070 
	float                Texture1X[0x0004];             // 0x0080 
	float                Texture1Y[0x0004];             // 0x0090 
	float                Texture1Z[0x0004];             // 0x00a0  
	float                Texture1W[0x0004];             // 0x00b0 
	float                ColorFrontR[0x0004];           // 0x00c0 
	float                ColorFrontG[0x0004];           // 0x00d0 
	float                ColorFrontB[0x0004];           // 0x00e0 
	float                ColorFrontA[0x0004];           // 0x00f0 
	float                NormalX[0x0004];               // 0x0100 
	float                NormalY[0x0004];               // 0x0110 
	float                NormalZ[0x0004];               // 0x0120 
	float                WindowX[0x0004];               // 0x0130 
	float                WindowY[0x0004];               // 0x0140 
	float                WindowZ[0x0004];               // 0x0150 
	float                WindowW[0x0004];               // 0x0160  
	float                EyeX[0x0004];                  // 0x0170 
	float                EyeY[0x0004];                  // 0x0180 
	float                EyeZ[0x0004];                  // 0x0190 
	float                EyeW[0x0004];                  // 0x01a0 
	float                ColorBackR[0x0004];            // 0x01b0 
	float                ColorBackG[0x0004];            // 0x01c0 
	float                ColorBackB[0x0004];            // 0x01d0 
	float                ColorBackA[0x0004];            // 0x01e0 
	float                Texture2X[0x0004];             // 0x01f0 
	float                Texture2Y[0x0004];             // 0x0200 
	float                Texture2Z[0x0004];             // 0x0210 
	float                Texture2W[0x0004];             // 0x0220  
	float                Texture3X[0x0004];             // 0x0230 
	float                Texture3Y[0x0004];             // 0x0240 
	float                Texture3Z[0x0004];             // 0x0250 
	float                Texture3W[0x0004];             // 0x0260 
	float                Texture4X[0x0004];             // 0x0270 
	float                Texture4Y[0x0004];             // 0x0280 
	float                Texture4Z[0x0004];             // 0x0290 
	float                Texture4W[0x0004];             // 0x02a0 
	unsigned int         ClipCode[0x0004];              // 0x02b0 
	int                  vertexBoundaryEdge[0x0004];    // 0x02c0  
	int                  Has[0x0004];                   // 0x02d0 
}; 

struct __glTextureMachineRec                    // 0x5a44 
{
	unsigned int         ActiveUnits;                   // 0x0000  RW	Texture units available in hardware.  Please initialize in accelerate_init 
	char                 Enabled[0x0004];               // 0x0004  R		Per texture unit enabled.  Factors in current state such as current texture and texture enables 
	void                 (*GenProc[4])( __glContext *gc, GLuint v ); // 0x0008 
	unsigned int         lastName;                      // 0x0018  NA 
	__glHashMap          Objects;                       // 0x001c  NA 
	__glTexture          Defaults[0x0006];              // 0x41bc  R		__GL_NUMBER_OF_TEXTURE_TARGETS] 
	__glTexture          *Active[0x0004];               // 0x5a34  R		Number of texture units 
}; 

struct __glVerticesMachineRec                   // 0x2d00 
{
	float                ObjX[0x0024];                  // 0x0000  
	float                ObjY[0x0024];                  // 0x0090 
	float                ObjZ[0x0024];                  // 0x0120 
	float                ObjW[0x0024];                  // 0x01b0 
	float                ClipX[0x0024];                 // 0x0240 
	float                ClipY[0x0024];                 // 0x02d0 
	float                ClipZ[0x0024];                 // 0x0360 
	float                ClipW[0x0024];                 // 0x03f0 
	float                TextureX[0x0024];              // 0x0480 
	float                TextureY[0x0024];              // 0x0510 
	float                TextureZ[0x0024];              // 0x05a0 
	float                TextureW[0x0024];              // 0x0630 
	float                FrontColorR[0x0024];           // 0x06c0 
	float                FrontColorG[0x0024];           // 0x0750 
	float                FrontColorB[0x0024];           // 0x07e0 
	float                FrontColorA[0x0024];           // 0x0870  
	float                NormalX[0x0024];               // 0x0900 
	float                NormalY[0x0024];               // 0x0990 
	float                NormalZ[0x0024];               // 0x0a20 
	float                WindowX[0x0024];               // 0x0ab0 
	float                WindowY[0x0024];               // 0x0b40 
	float                WindowZ[0x0024];               // 0x0bd0 
	float                WindowW[0x0024];               // 0x0c60 
	float                EyeX[0x0024];                  // 0x0cf0 
	float                EyeY[0x0024];                  // 0x0d80 
	float                EyeZ[0x0024];                  // 0x0e10 
	float                EyeW[0x0024];                  // 0x0ea0 
	float                BackColorR[0x0024];            // 0x0f30 
	float                BackColorG[0x0024];            // 0x0fc0 
	float                BackColorB[0x0024];            // 0x1050  
	float                BackColorA[0x0024];            // 0x10e0 
	float                Texture2X[0x0024];             // 0x1170 
	float                Texture2Y[0x0024];             // 0x1200 
	float                Texture2Z[0x0024];             // 0x1290 
	float                Texture2W[0x0024];             // 0x1320 
	float                Texture3X[0x0024];             // 0x13b0 
	float                Texture3Y[0x0024];             // 0x1440 
	float                Texture3Z[0x0024];             // 0x14d0 
	float                Texture3W[0x0024];             // 0x1560 
	float                Texture4X[0x0024];             // 0x15f0 
	float                Texture4Y[0x0024];             // 0x1680 
	float                Texture4Z[0x0024];             // 0x1710 
	float                Texture4W[0x0024];             // 0x17a0  
	unsigned int         ClipCode[0x0024];              // 0x1830 
	int                  Edge[0x0024];                  // 0x18c0 
	int                  Has[0x0024];                   // 0x1950 
	float                FrontAmbientR[0x0024];         // 0x19e0 
	float                FrontAmbientG[0x0024];         // 0x1a70 
	float                FrontAmbientB[0x0024];         // 0x1b00 
	float                FrontAmbientA[0x0024];         // 0x1b90 
	float                FrontDiffuseR[0x0024];         // 0x1c20 
	float                FrontDiffuseG[0x0024];         // 0x1cb0 
	float                FrontDiffuseB[0x0024];         // 0x1d40 
	float                FrontDiffuseA[0x0024];         // 0x1dd0 
	float                FrontSpecularR[0x0024];        // 0x1e60 
	float                FrontSpecularG[0x0024];        // 0x1ef0 
	float                FrontSpecularB[0x0024];        // 0x1f80 
	float                FrontSpecularA[0x0024];        // 0x2010 
	float                FrontSceneR[0x0024];           // 0x20a0 
	float                FrontSceneG[0x0024];           // 0x2130 
	float                FrontSceneB[0x0024];           // 0x21c0 
	float                FrontSceneA[0x0024];           // 0x2250 
	float                FrontSpecExp[0x0024];          // 0x22e0 
	float                BackAmbientR[0x0024];          // 0x2370 
	float                BackAmbientG[0x0024];          // 0x2400 
	float                BackAmbientB[0x0024];          // 0x2490 
	float                BackAmbientA[0x0024];          // 0x2520 
	float                BackDiffuseR[0x0024];          // 0x25b0 
	float                BackDiffuseG[0x0024];          // 0x2640 
	float                BackDiffuseB[0x0024];          // 0x26d0 
	float                BackDiffuseA[0x0024];          // 0x2760 
	float                BackSpecularR[0x0024];         // 0x27f0 
	float                BackSpecularG[0x0024];         // 0x2880 
	float                BackSpecularB[0x0024];         // 0x2910 
	float                BackSpecularA[0x0024];         // 0x29a0 
	float                BackSceneR[0x0024];            // 0x2a30 
	float                BackSceneG[0x0024];            // 0x2ac0 
	float                BackSceneB[0x0024];            // 0x2b50 
	float                BackSceneA[0x0024];            // 0x2be0 
	float                BackSpecExp[0x0024];           // 0x2c70 
}; 

struct __glInfoRec                              // 0x003c 
{
	unsigned int         state_h_version;               // 0x0000  R 
	unsigned int         textureMaxS;                   // 0x0004  RW 
	unsigned int         textureMaxT;                   // 0x0008  RW 
	unsigned int         textureMaxR;                   // 0x000c  RW 
	char                 *vendor;                       // 0x0010  R  
	char                 *renderer;                     // 0x0014  R 
	char                 *version;                      // 0x0018  R 
	char                 *extensions;                   // 0x001c  R 
	char                 *hwRenderer;                   // 0x0020  RW Defaults to null, set string to name of HW renderer if present 
	char                 *hwGeometry;                   // 0x0024  RW Defaults to null, set string to name of HW geometry if present 
	char                 *comboStrings[0x0003];         // 0x0028  R  The three strings that are possible for GL_RENDERER 
	unsigned char        debugLock;                     // 0x0034  R 
	unsigned char        debugDevices;                  // 0x0035  R 
	unsigned char        debugDriver;                   // 0x0036  R 
	unsigned char        debugModes;                    // 0x0037  R 
	unsigned char        debugOther;                    // 0x0038  R 
	unsigned char        debugDisableDCLock;            // 0x0039  R 
	char                 _padding_03a[2]; 
}; 

struct __glWindowStateRec                       // 0x0008  Container for window related state. 
{
	int                  UtilThreadSem;                 // 0x0000  R sem_id that triggers the util thread.  Releasing it will trigger a call to processThreadEvent. 
	void                 *DirectWindow;                 // 0x0004  NA 
}; 

struct __glContextRec                           // 0xd9c0 
{
	__glProcTable        *procTable;                    // 0x0000 
	char                 _padding_004[12]; 
	__glVerticesMachine  vertices;                      // 0x0010 
	__glMatrixSIMD       mvp;                           // 0x2d10 
	__glMatrixSIMD       model;                         // 0x2e10 
	__glMatrixSIMD       invModel;                      // 0x2f10  
	int                  isRendering;                   // 0x3010  1 for immediate mode, 0 for building display list. 
	void                 (*polyClipParam) ();           // 0x3014  All args in regs 
	unsigned int         nextClipTemp;                  // 0x3018 
	void                 (*asmProc_Light)();            // 0x301c 
	void                 (*asmProc_EWNT_Front)();       // 0x3020  
	void                 (*asmProc_EWNT_Back)();        // 0x3024 
	int                  renderMode;                    // 0x3028 
	int                  error;                         // 0x302c 
	int                  auxBuffers;                    // 0x3030 
	int                  stencilBufferBits;             // 0x3034  
	char                 _padding_3038[8]; 
	rasState             state;                         // 0x3040 
	__glTextureMachine   texture;                       // 0x3e00 
	char                 _padding_9844[12]; 
	__glViewportMachine  viewport;                      // 0x9850 
	__glDriverProcs      procs;                         // 0x98c0 
	__glPrimitiveMachine primitive;                     // 0x9aec 
	__glClipInfoStruct   *clipInfo;                     // 0x9d08  
	__glSoftwareMachine  software;                      // 0x9d0c 
	__glBufferMachine    buffer;                        // 0x9d10 
	__glValidMachine     valid;                         // 0x9dc8 
	__glMethods          methods;                       // 0x9df0 
	__glAttributeMachine attributes;                    // 0x9e14 
	__glVertexMachine    vertex;                        // 0x9e9c 
	__glTransformMachine transform;                     // 0x9f78 
	__glListMachine      list;                          // 0xc760 
	__glEvaluatorMachine evaluator;                     // 0xc774 
	__glFeedbackMachine  feedback;                      // 0xc948 
	__glLineMachine      line;                          // 0xc95c 
	__glSelectMachine    select;                        // 0xc964 
	char                 _padding_cb84[12]; 
	__glLightMachine     light;                         // 0xcb90 
	__glVertexArrayMachine vertexArray;                   // 0xd560 
	__glSoftwareScanlineProcs softScanProcs;                 // 0xd600  
	__glInfo             info;                          // 0xd61c 
	__glWindowState      window;                        // 0xd658 
	__glProcTable        immedTable;                    // 0xd660 
	void                 *flingerContext;               // 0xd9a4 
	int                  flingerCurrent;                // 0xd9a8 
	int                  flingerLOD;                    // 0xd9ac 
	void                 *usrVp1;                       // 0xd9b0 
	void                 *usrVp2;                       // 0xd9b4 
	void                 *usrVp3;                       // 0xd9b8 
	void                 *usrVp4;                       // 0xd9bc 
}; 

#endif 
