%ifndef __state_inc__ 
%define __state_inc__ 

%define __state_h__VERSION 0x60b5909b 

%define __GL_NUMBER_OF_TEXTURE_TARGETS 6
%define __GL_TEXTURE_INDEX_1D 0
%define __GL_TEXTURE_INDEX_2D 1
%define __GL_TEXTURE_INDEX_3D 2
%define __GL_PROXY_TEXTURE_INDEX_1D 3
%define __GL_PROXY_TEXTURE_INDEX_2D 4
%define __GL_PROXY_TEXTURE_INDEX_3D 5
%define __GL_MAX_TMU_COUNT 4
%define __GL_PERFORM_NOP 0
%define __GL_PERFORM_DESTROY_BUFFERS 1
%define __GL_PERFORM_CREATE_BUFFERS 2


%define SIZEOF___glCoord 0x10
STRUC __glCoord                                      
.X                                    resd 0x001; 0x0000
.Y                                    resd 0x001; 0x0004
.Z                                    resd 0x001; 0x0008
.W                                    resd 0x001; 0x000c
ENDSTRUC 

%define SIZEOF___glColor 0x10
STRUC __glColor                                      
.R                                    resd 0x001; 0x0000
.G                                    resd 0x001; 0x0004
.B                                    resd 0x001; 0x0008
.A                                    resd 0x001; 0x000c
ENDSTRUC 

%define SIZEOF___glMaterialState 0x144
STRUC __glMaterialState                              ;  NA 
.Ambient_R                            resd 0x001; 0x0000
.Ambient_G                            resd 0x001; 0x0004
.Ambient_B                            resd 0x001; 0x0008
.Ambient_A                            resd 0x001; 0x000c
.Diffuse_R                            resd 0x001; 0x0010
.Diffuse_G                            resd 0x001; 0x0014
.Diffuse_B                            resd 0x001; 0x0018
.Diffuse_A                            resd 0x001; 0x001c
.Specular_R                           resd 0x001; 0x0020
.Specular_G                           resd 0x001; 0x0024
.Specular_B                           resd 0x001; 0x0028
.Specular_A                           resd 0x001; 0x002c
.Emissive_R                           resd 0x001; 0x0030
.Emissive_G                           resd 0x001; 0x0034
.Emissive_B                           resd 0x001; 0x0038
.Emissive_A                           resd 0x001; 0x003c
.SpecExp                              resd 0x001; 0x0040
.SpecExpTable                         resb 0x100; 0x0044
ENDSTRUC 

%define SIZEOF___glPerLightState 0x78
STRUC __glPerLightState                              ;  NA 
.Enabled                              resb 0x001; 0x0000
.padding_001                          resb 0x003 
.Ambient_R                            resd 0x001; 0x0004
.Ambient_G                            resd 0x001; 0x0008
.Ambient_B                            resd 0x001; 0x000c
.Ambient_A                            resd 0x001; 0x0010
.Diffuse_R                            resd 0x001; 0x0014
.Diffuse_G                            resd 0x001; 0x0018
.Diffuse_B                            resd 0x001; 0x001c
.Diffuse_A                            resd 0x001; 0x0020
.Specular_R                           resd 0x001; 0x0024
.Specular_G                           resd 0x001; 0x0028
.Specular_B                           resd 0x001; 0x002c
.Specular_A                           resd 0x001; 0x0030
.Position_X                           resd 0x001; 0x0034
.Position_Y                           resd 0x001; 0x0038
.Position_Z                           resd 0x001; 0x003c
.Position_W                           resd 0x001; 0x0040
.PositionEye_X                        resd 0x001; 0x0044
.PositionEye_Y                        resd 0x001; 0x0048
.PositionEye_Z                        resd 0x001; 0x004c
.PositionEye_W                        resd 0x001; 0x0050
.Direction_X                          resd 0x001; 0x0054
.Direction_Y                          resd 0x001; 0x0058
.Direction_Z                          resd 0x001; 0x005c
.Direction_W                          resd 0x001; 0x0060
.Exponent                             resd 0x001; 0x0064
.CutOffAngle                          resd 0x001; 0x0068
.ConstantAttenuation                  resd 0x001; 0x006c
.LinearAttenuation                    resd 0x001; 0x0070
.QuadraticAttenuation                 resd 0x001; 0x0074
ENDSTRUC 

%define SIZEOF___glLightState 0x66c
STRUC __glLightState                                 
.LightingEnabled                      resb 0x001; 0x0000  NA 
.ColorMaterialEnabled                 resb 0x001; 0x0001  NA 
.padding_002                          resb 0x002 
.ColorMaterialFace                    resd 0x001; 0x0004  NA 
.ColorMaterialParam                   resd 0x001; 0x0008  NA 
.ShadingModel                         resd 0x001; 0x000c  R		Flat or smooth triangle shading 
.AmbientLightColor_R                  resd 0x001; 0x0010
.AmbientLightColor_G                  resd 0x001; 0x0014
.AmbientLightColor_B                  resd 0x001; 0x0018
.AmbientLightColor_A                  resd 0x001; 0x001c
.LocalViewerEnabled                   resb 0x001; 0x0020  NA 
.TwoSidedEnabled                      resb 0x001; 0x0021  R		If enabled you may see back side triangles 
.padding_022                          resb 0x002 
.material                             resb 0x288; 0x0024  NA	Front & Back 
.light                                resb 0x3c0; 0x02ac  NA 
ENDSTRUC 

%define SIZEOF___glPolygonState 0x24
STRUC __glPolygonState                               ;  NA 
.FrontFaceDirection                   resd 0x001; 0x0000  R		Winding direction for the fron of a triangle.  GL_CW or GL_CCW 
.FrontMode                            resd 0x001; 0x0004  R		Drawing mode for the front of a triangle.  GL_FILL, GL_LINE, GL_POINT 
.BackMode                             resd 0x001; 0x0008  R		Drawing mode for the back of a triangle.  GL_FILL, GL_LINE, GL_POINT 
.Cull                                 resd 0x001; 0x000c  R		Culling mode.  GL_FRONT, GL_BACK, GL_FRON_AND_BACK 
.OffsetFactor                         resd 0x001; 0x0010  R		Polygon offset factor 
.OffsetUnit                           resd 0x001; 0x0014  R		Polygon offset unit 
.OffsetR                              resd 0x001; 0x0018  NA 
.CullFaceEnabled                      resb 0x001; 0x001c  R		Culling enable.  Note: culling is done in software and is not necessary in the driver 
.SmoothEnabled                        resb 0x001; 0x001d  R		Polygon anti-aliasing enable 
.OffsetPointEnabled                   resb 0x001; 0x001e  R		Polygon Offset for Point mode enable 
.OffsetLineEnabled                    resb 0x001; 0x001f  R		Polygon Offset for Line mode enable 
.OffsetFillEnabled                    resb 0x001; 0x0020  R		Polygon Offset for Fill mode enable 
.StippleEnabled                       resb 0x001; 0x0021  R		Polygon stipple enable 
.padding_022                          resb 0x002 
ENDSTRUC 

%define SIZEOF___glDepthState 0x10
STRUC __glDepthState                                 
.TestEnabled                          resb 0x001; 0x0000  R		Depth test enable 
.padding_001                          resb 0x003 
.TestFunction                         resd 0x001; 0x0004  R		Depth test function 
.ClearValue                           resd 0x001; 0x0008  R		Depth buffer clear value 
.WriteEnabled                         resb 0x001; 0x000c  R		Depth test write enable 
.padding_00d                          resb 0x003 
ENDSTRUC 

%define SIZEOF___glColorState 0x28
STRUC __glColorState                                 
.RedWriteEnabled                      resb 0x001; 0x0000  R		Red Component write enable 
.GreenWriteEnabled                    resb 0x001; 0x0001  R		Green Component write enable 
.BlueWriteEnabled                     resb 0x001; 0x0002  R		Blue Component write enable 
.AlphaWriteEnabled                    resb 0x001; 0x0003  R		Alpha Component write enable 
.ClearValue_R                         resd 0x001; 0x0004
.ClearValue_G                         resd 0x001; 0x0008
.ClearValue_B                         resd 0x001; 0x000c
.ClearValue_A                         resd 0x001; 0x0010
.BlendEnabled                         resb 0x001; 0x0014  R		Color blending enable 
.padding_015                          resb 0x003 
.BlendSrcFunction                     resd 0x001; 0x0018  R		Color blending source function 
.BlendDestFunction                    resd 0x001; 0x001c  R		Color blending destination function 
.LogicOp                              resd 0x001; 0x0020  R		Color buffer logical operation 
.LogicOpEnabled                       resb 0x001; 0x0024  R		Logical operation enable 
.DitherEnabled                        resb 0x001; 0x0025  R		Dithering enable 
.padding_026                          resb 0x002 
ENDSTRUC 

%define SIZEOF___glStencilState 0x24
STRUC __glStencilState                               
.TestEnabled                          resb 0x001; 0x0000  R		Stencil test enabled 
.padding_001                          resb 0x003 
.ClearValue                           resd 0x001; 0x0004  R		Stencil clear value 
.WriteMask                            resd 0x001; 0x0008  R		Stencil write mask 
.Function                             resd 0x001; 0x000c  R		Stencil function 
.Refrence                             resd 0x001; 0x0010  R		Stencil refrence value 
.FunctionMask                         resd 0x001; 0x0014  R		Stencil function mask 
.FailOp                               resd 0x001; 0x0018  R		Stencil Fail Operation 
.DepthFailOp                          resd 0x001; 0x001c  R		Stencil depth test fail operation 
.DepthPassOp                          resd 0x001; 0x0020  R		Stencil depth test pass operation 
ENDSTRUC 

%define SIZEOF___glTextureCoordState 0x24
STRUC __glTextureCoordState                          
.mode                                 resd 0x001; 0x0000  NA	How coordinates are being generated 
.eyePlaneEquation_X                   resd 0x001; 0x0004
.eyePlaneEquation_Y                   resd 0x001; 0x0008
.eyePlaneEquation_Z                   resd 0x001; 0x000c
.eyePlaneEquation_W                   resd 0x001; 0x0010
.objectPlaneEquation_X                resd 0x001; 0x0014
.objectPlaneEquation_Y                resd 0x001; 0x0018
.objectPlaneEquation_Z                resd 0x001; 0x001c
.objectPlaneEquation_W                resd 0x001; 0x0020
ENDSTRUC 

%define SIZEOF___glXformState 0x6c
STRUC __glXformState                                 ;  NA, Will be used for T&L 
.Normalize                            resb 0x001; 0x0000
.padding_001                          resb 0x003 
.ClipPlanesMask                       resd 0x001; 0x0004
.MatrixMode                           resd 0x001; 0x0008
.EyeClipPlanes                        resb 0x060; 0x000c
ENDSTRUC 

%define SIZEOF___glViewportState 0x18
STRUC __glViewportState                              ;  NA, Will be used for T&L 
.X                                    resd 0x001; 0x0000
.Y                                    resd 0x001; 0x0004
.Width                                resd 0x001; 0x0008
.Height                               resd 0x001; 0x000c
.ZNear                                resd 0x001; 0x0010
.ZFar                                 resd 0x001; 0x0014
ENDSTRUC 

%define SIZEOF___glScissorState 0x14
STRUC __glScissorState                               
.Enabled                              resb 0x001; 0x0000  R		Scissors enable 
.padding_001                          resb 0x003 
.X                                    resd 0x001; 0x0004  R		Left of scissor region, inclusive 
.Y                                    resd 0x001; 0x0008  R		Bottom of scissor region, inclusive 
.Width                                resd 0x001; 0x000c  R		Width of scissor region 
.Height                               resd 0x001; 0x0010  R		Height of scissor region 
ENDSTRUC 

%define SIZEOF___glHintState 0x14
STRUC __glHintState                                  
.PerspectiveCorrection                resd 0x001; 0x0000  R 
.PointSmooth                          resd 0x001; 0x0004  R 
.LineSmooth                           resd 0x001; 0x0008  R 
.PolygonSmooth                        resd 0x001; 0x000c  R 
.Fog                                  resd 0x001; 0x0010  R 
ENDSTRUC 

%define SIZEOF___glAccumState 0x10
STRUC __glAccumState                                 
.ClearColor_R                         resd 0x001; 0x0000
.ClearColor_G                         resd 0x001; 0x0004
.ClearColor_B                         resd 0x001; 0x0008
.ClearColor_A                         resd 0x001; 0x000c
ENDSTRUC 

%define SIZEOF___glFogState 0x24
STRUC __glFogState                                   
.Color_R                              resd 0x001; 0x0000
.Color_G                              resd 0x001; 0x0004
.Color_B                              resd 0x001; 0x0008
.Color_A                              resd 0x001; 0x000c
.Enabled                              resb 0x001; 0x0010  R		Fogging enabled 
.padding_011                          resb 0x003 
.Mode                                 resd 0x001; 0x0014  R		Fog Mode (linear, exp, exp2) 
.Density                              resd 0x001; 0x0018  R		Fog density 
.Start                                resd 0x001; 0x001c  R		Fog start 
.End                                  resd 0x001; 0x0020  R		Fog end 
ENDSTRUC 

%define SIZEOF___glLineState 0x18
STRUC __glLineState                                  
.SmoothEnabled                        resb 0x001; 0x0000  R		Anti-Alaising 
.padding_001                          resb 0x003 
.RequestedWidth                       resd 0x001; 0x0004  R 
.SmoothWidth                          resd 0x001; 0x0008  R 
.AliasedWidth                         resd 0x001; 0x000c  R 
.StippleEnabled                       resb 0x001; 0x0010  R 
.padding_011                          resb 0x001 
.StippleMask                          resw 0x001; 0x0012  R 
.StippleRepeat                        resd 0x001; 0x0014  R 
ENDSTRUC 

%define SIZEOF___glPointState 0x10
STRUC __glPointState                                 
.SmoothEnabled                        resb 0x001; 0x0000  R		Anti-Alaising 
.padding_001                          resb 0x003 
.SizeRequested                        resd 0x001; 0x0004  R 
.SmoothSize                           resd 0x001; 0x0008  R 
.AliasedSize                          resd 0x001; 0x000c  R 
ENDSTRUC 

%define SIZEOF___glAlphaState 0xc
STRUC __glAlphaState                                 
.TestEnabled                          resb 0x001; 0x0000  R		 
.padding_001                          resb 0x003 
.TestFunction                         resd 0x001; 0x0004  R 
.TestValue                            resd 0x001; 0x0008  R		Float 0.0 to 1.0 
ENDSTRUC 

%define SIZEOF___glOptimizationState 0x10
STRUC __glOptimizationState                          
.UseTempColor                         resb 0x001; 0x0000  NA 
.UseTempTex                           resb 0x004; 0x0001  NA 
.UseTempNormal                        resb 0x001; 0x0005  NA 
.UseTempEdge                          resb 0x001; 0x0006  NA 
.Tex2                                 resb 0x004; 0x0007  R		Per TMU, when set all texture coords R=0, W=1 
.Tex3                                 resb 0x004; 0x000b  R		Per TMU, when set all texture coords W=1 
.padding_00f                          resb 0x001 
ENDSTRUC 

%define SIZEOF___glCurrentState2 0x74
STRUC __glCurrentState2                              ;  NA 
.Normal_X                             resd 0x001; 0x0000
.Normal_Y                             resd 0x001; 0x0004
.Normal_Z                             resd 0x001; 0x0008
.Normal_W                             resd 0x001; 0x000c
.UserColor_R                          resd 0x001; 0x0010
.UserColor_G                          resd 0x001; 0x0014
.UserColor_B                          resd 0x001; 0x0018
.UserColor_A                          resd 0x001; 0x001c
.Color_R                              resd 0x001; 0x0020
.Color_G                              resd 0x001; 0x0024
.Color_B                              resd 0x001; 0x0028
.Color_A                              resd 0x001; 0x002c
.Texture1_X                           resd 0x001; 0x0030
.Texture1_Y                           resd 0x001; 0x0034
.Texture1_Z                           resd 0x001; 0x0038
.Texture1_W                           resd 0x001; 0x003c
.Texture2_X                           resd 0x001; 0x0040
.Texture2_Y                           resd 0x001; 0x0044
.Texture2_Z                           resd 0x001; 0x0048
.Texture2_W                           resd 0x001; 0x004c
.Texture3_X                           resd 0x001; 0x0050
.Texture3_Y                           resd 0x001; 0x0054
.Texture3_Z                           resd 0x001; 0x0058
.Texture3_W                           resd 0x001; 0x005c
.Texture4_X                           resd 0x001; 0x0060
.Texture4_Y                           resd 0x001; 0x0064
.Texture4_Z                           resd 0x001; 0x0068
.Texture4_W                           resd 0x001; 0x006c
.Edge                                 resd 0x001; 0x0070
ENDSTRUC 

%define SIZEOF___glPixelMapHead 0x8
STRUC __glPixelMapHead                               ;  NA 
.Size                                 resd 0x001; 0x0000
.Map                                  resd 0x001; 0x0004
ENDSTRUC 

%define SIZEOF___glPixelTransferMode 0x3c
STRUC __glPixelTransferMode                          ;  Read Only 
.ScaleR                               resd 0x001; 0x0000
.ScaleG                               resd 0x001; 0x0004
.ScaleB                               resd 0x001; 0x0008
.ScaleA                               resd 0x001; 0x000c
.ScaleD                               resd 0x001; 0x0010
.BiasR                                resd 0x001; 0x0014
.BiasG                                resd 0x001; 0x0018
.BiasB                                resd 0x001; 0x001c
.BiasA                                resd 0x001; 0x0020
.BiasD                                resd 0x001; 0x0024
.ZoomX                                resd 0x001; 0x0028
.ZoomY                                resd 0x001; 0x002c
.IndexShift                           resd 0x001; 0x0030
.IndexOffset                          resd 0x001; 0x0034
.MapColor                             resb 0x001; 0x0038
.MapStencil                           resb 0x001; 0x0039
.padding_03a                          resb 0x002 
ENDSTRUC 

%define SIZEOF___glPixelPackMode 0x14
STRUC __glPixelPackMode                              ;  Read Only 
.SwapEndian                           resb 0x001; 0x0000  
.LsbFirst                             resb 0x001; 0x0001
.padding_002                          resb 0x002 
.LineLength                           resd 0x001; 0x0004
.SkipLines                            resd 0x001; 0x0008
.SkipPixels                           resd 0x001; 0x000c
.Alignment                            resd 0x001; 0x0010
ENDSTRUC 

%define SIZEOF___glPixelUnpackMode 0x14
STRUC __glPixelUnpackMode                            ;  Read Only 
.SwapEndian                           resb 0x001; 0x0000  
.LsbFirst                             resb 0x001; 0x0001
.padding_002                          resb 0x002 
.LineLength                           resd 0x001; 0x0004
.SkipLines                            resd 0x001; 0x0008
.SkipPixels                           resd 0x001; 0x000c
.Alignment                            resd 0x001; 0x0010
ENDSTRUC 

%define SIZEOF___glPixel 0x20
STRUC __glPixel                                      
.Format                               resd 0x001; 0x0000  
.R                                    resd 0x001; 0x0004
.G                                    resd 0x001; 0x0008
.B                                    resd 0x001; 0x000c
.A                                    resd 0x001; 0x0010
.D                                    resd 0x001; 0x0014
.Index                                resd 0x001; 0x0018
.Fraction                             resd 0x001; 0x001c
ENDSTRUC 

%define SIZEOF___glPixelState 0xbc
STRUC __glPixelState                                 ;  R		This structure contains the state needed for the driver to handle packing and unpacking of user pixel data.  Only needed if the driver is doing its own texture management. 
.transferMode_ScaleR                  resd 0x001; 0x0000
.transferMode_ScaleG                  resd 0x001; 0x0004
.transferMode_ScaleB                  resd 0x001; 0x0008
.transferMode_ScaleA                  resd 0x001; 0x000c
.transferMode_ScaleD                  resd 0x001; 0x0010
.transferMode_BiasR                   resd 0x001; 0x0014
.transferMode_BiasG                   resd 0x001; 0x0018
.transferMode_BiasB                   resd 0x001; 0x001c
.transferMode_BiasA                   resd 0x001; 0x0020
.transferMode_BiasD                   resd 0x001; 0x0024
.transferMode_ZoomX                   resd 0x001; 0x0028
.transferMode_ZoomY                   resd 0x001; 0x002c
.transferMode_IndexShift              resd 0x001; 0x0030
.transferMode_IndexOffset             resd 0x001; 0x0034
.transferMode_MapColor                resb 0x001; 0x0038
.transferMode_MapStencil              resb 0x001; 0x0039
.padding_03a                          resb 0x002 
.packModes_SwapEndian                 resb 0x001; 0x003c  
.packModes_LsbFirst                   resb 0x001; 0x003d
.padding_03e                          resb 0x002 
.packModes_LineLength                 resd 0x001; 0x0040
.packModes_SkipLines                  resd 0x001; 0x0044
.packModes_SkipPixels                 resd 0x001; 0x0048
.packModes_Alignment                  resd 0x001; 0x004c
.unpackModes_SwapEndian               resb 0x001; 0x0050  
.unpackModes_LsbFirst                 resb 0x001; 0x0051
.padding_052                          resb 0x002 
.unpackModes_LineLength               resd 0x001; 0x0054
.unpackModes_SkipLines                resd 0x001; 0x0058
.unpackModes_SkipPixels               resd 0x001; 0x005c
.unpackModes_Alignment                resd 0x001; 0x0060
.pixelMap                             resb 0x050; 0x0064  R		__GL_N_PIXEL_MAPS 
.ReadBuffer                           resd 0x001; 0x00b4  R 
.ReadBufferReturn                     resd 0x001; 0x00b8  R 
ENDSTRUC 

%define SIZEOF___glEvaluatorGrid 0xc
STRUC __glEvaluatorGrid                              ;  NA 
.Start                                resd 0x001; 0x0000  
.Finish                               resd 0x001; 0x0004
.N                                    resd 0x001; 0x0008
ENDSTRUC 

%define SIZEOF___glEvaluatorState 0x38
STRUC __glEvaluatorState                             ;  NA 
.u1_Start                             resd 0x001; 0x0000  
.u1_Finish                            resd 0x001; 0x0004
.u1_N                                 resd 0x001; 0x0008
.u2_Start                             resd 0x001; 0x000c  
.u2_Finish                            resd 0x001; 0x0010
.u2_N                                 resd 0x001; 0x0014
.v2_Start                             resd 0x001; 0x0018  
.v2_Finish                            resd 0x001; 0x001c
.v2_N                                 resd 0x001; 0x0020
.Map1Enabled                          resb 0x009; 0x0024  __GL_MAP_RANGE_COUNT 
.Map2Enabled                          resb 0x009; 0x002d  __GL_MAP_RANGE_COUNT 
.AutonormalEnabled                    resb 0x001; 0x0036
.padding_037                          resb 0x001 
ENDSTRUC 

%define SIZEOF___glListState 0x4
STRUC __glListState                                  ;  NA 
.ListBase                             resd 0x001; 0x0000
ENDSTRUC 

%define SIZEOF___glVertArrayState 0x90
STRUC __glVertArrayState                             ;  NA 
.SelectedTextureUnit                  resd 0x001; 0x0000
.VertexPtr                            resd 0x001; 0x0004  
.VertexSize                           resd 0x001; 0x0008
.VertexType                           resd 0x001; 0x000c
.VertexStride                         resd 0x001; 0x0010
.NormalPtr                            resd 0x001; 0x0014
.NormalType                           resd 0x001; 0x0018
.NormalStride                         resd 0x001; 0x001c
.ColorPtr                             resd 0x001; 0x0020
.ColorSize                            resd 0x001; 0x0024
.ColorType                            resd 0x001; 0x0028
.ColorStride                          resd 0x001; 0x002c
.IndexPtr                             resd 0x001; 0x0030
.IndexType                            resd 0x001; 0x0034
.IndexStride                          resd 0x001; 0x0038  
.TexCoordPtr                          resd 0x004; 0x003c
.TexCoordSize                         resd 0x004; 0x004c
.TexCoordType                         resd 0x004; 0x005c
.TexCoordStride                       resd 0x004; 0x006c
.EdgeFlagPtr                          resd 0x001; 0x007c
.EdgeFlagStride                       resd 0x001; 0x0080
.VertexArrayEnabled                   resb 0x001; 0x0084
.NormalArrayEnabled                   resb 0x001; 0x0085
.ColorArrayEnabled                    resb 0x001; 0x0086
.IndexArrayEnabled                    resb 0x001; 0x0087
.TexCoordArrayEnabled                 resb 0x004; 0x0088
.EdgeFlagArrayEnabled                 resb 0x001; 0x008c  
.padding_08d                          resb 0x003 
ENDSTRUC 

%define SIZEOF___glTextureLevel 0x58
STRUC __glTextureLevel                               
.requestedFormat                      resd 0x001; 0x0000  R		The format requested by the user. 
.border                               resd 0x001; 0x0004  R		Border size 
.data                                 resd 0x001; 0x0008  R		Pointer to the raw data. NULL if the driver took control. 
.width                                resd 0x001; 0x000c  R		Image dimensions, including border. 
.height                               resd 0x001; 0x0010  R		Image dimensions, including border. 
.width2                               resd 0x001; 0x0014  R		Image dimensions, excluding border. 
.height2                              resd 0x001; 0x0018  R		Image dimensions, excluding border. 
.baseFormat                           resd 0x001; 0x001c  R		Base internal format.  GL_ALPHA, GL_RGB, ...  Without bit count. 
.internalFormat                       resd 0x001; 0x0020  RW	Internal format (count and ordering of components). 
.internalType                         resd 0x001; 0x0024  RW	Internal type.  GL 1.2 types. 
.allocationSize                       resd 0x001; 0x0028  R 
.bytesPerTexel                        resd 0x001; 0x002c  RW 
.sizeR                                resd 0x001; 0x0030  RW	Bits of Red per component 
.sizeG                                resd 0x001; 0x0034  RW	Bits of Green per component 
.sizeB                                resd 0x001; 0x0038  RW	Bits of Blue per component 
.sizeA                                resd 0x001; 0x003c  RW	Bits of Alpha per component 
.sizeL                                resd 0x001; 0x0040  RW	Bits of Luminance per component 
.sizeI                                resd 0x001; 0x0044  RW	Bits of Intensity per component 
.usr_vp1                              resd 0x001; 0x0048  RW	User defined pointer, used by driver to store any special info. 
.usr_vp2                              resd 0x001; 0x004c  RW	User defined pointer, used by driver to store any special info. 
.usr_i1                               resd 0x001; 0x0050  RW	User defined int, used by driver to store any special info. 
.usr_i2                               resd 0x001; 0x0054  RW	User defined int, used by driver to store any special info. 
ENDSTRUC 

%define SIZEOF___glTexture 0x414
STRUC __glTexture                                    
.borderColor_R                        resd 0x001; 0x0000
.borderColor_G                        resd 0x001; 0x0004
.borderColor_B                        resd 0x001; 0x0008
.borderColor_A                        resd 0x001; 0x000c
.sWrapMode                            resd 0x001; 0x0010  R		X 
.tWrapMode                            resd 0x001; 0x0014  R		Y 
.rWrapMode                            resd 0x001; 0x0018  R		Z 
.minFilter                            resd 0x001; 0x001c  R		The filter for texture minification. 
.magFilter                            resd 0x001; 0x0020  R		The filter for texture magnification. 
.name                                 resd 0x001; 0x0024  R		The texture object name 
.priority                             resd 0x001; 0x0028  R		Float 0.0 to 1.0 
.hasMipmaps                           resb 0x001; 0x002c  R 
.isValid                              resb 0x001; 0x002d  R		Is it in a valid state 
.padding_02e                          resb 0x002 
.level                                resb 0x3c8; 0x0030  		RAS_MAX_MIPMAP_LEVEL, The individual mipmaps. 
.activeLevels                         resd 0x001; 0x03f8  R 
.dim                                  resd 0x001; 0x03fc  R		Dimension of this texture (1, 2, or 3) 
.textureFunc                          resd 0x001; 0x0400  NA 
.usr_vp1                              resd 0x001; 0x0404  RW	User defined pointer, used by driver to store any special info 
.usr_vp2                              resd 0x001; 0x0408  RW	User defined pointer, used by driver to store any special info 
.usr_i1                               resd 0x001; 0x040c  RW	User defined int, used by driver to store any special info 
.usr_i2                               resd 0x001; 0x0410  RW	User defined int, used by driver to store any special info 
ENDSTRUC 

%define SIZEOF___glTextureState2 0x310
STRUC __glTextureState2                              
.Bound                                resd 0x018; 0x0000  R		__GL_NUMBER_OF_TEXTURE_TARGETS * TextureUnits] 
.s                                    resb 0x090; 0x0060  R		Texture Gen state per TMU 
.t                                    resb 0x090; 0x00f0  R		Texture Gen state per TMU 
.r                                    resb 0x090; 0x0180  R		Texture Gen state per TMU 
.q                                    resb 0x090; 0x0210  R		Texture Gen state per TMU 
.SelectedUnit                         resd 0x001; 0x02a0  R		Currently selected texture unit 
.Enabled1D                            resb 0x004; 0x02a4  R		Texture 1D Enable state per TMU 
.Enabled2D                            resb 0x004; 0x02a8  R		Texture 2D Enable state per TMU 
.Enabled3D                            resb 0x004; 0x02ac  R		Texture 3D Enable state per TMU 
.EnvMode                              resd 0x004; 0x02b0  R 
.EnvColor                             resb 0x040; 0x02c0  R 
.GenEnabled                           resb 0x010; 0x0300  NA	Texture GenEnable[tmu][coord] 
ENDSTRUC 

%define SIZEOF_rasState 0xdc0
STRUC rasState                                       
.poly_FrontFaceDirection              resd 0x001; 0x0000  R		Winding direction for the fron of a triangle.  GL_CW or GL_CCW 
.poly_FrontMode                       resd 0x001; 0x0004  R		Drawing mode for the front of a triangle.  GL_FILL, GL_LINE, GL_POINT 
.poly_BackMode                        resd 0x001; 0x0008  R		Drawing mode for the back of a triangle.  GL_FILL, GL_LINE, GL_POINT 
.poly_Cull                            resd 0x001; 0x000c  R		Culling mode.  GL_FRONT, GL_BACK, GL_FRON_AND_BACK 
.poly_OffsetFactor                    resd 0x001; 0x0010  R		Polygon offset factor 
.poly_OffsetUnit                      resd 0x001; 0x0014  R		Polygon offset unit 
.poly_OffsetR                         resd 0x001; 0x0018  NA 
.poly_CullFaceEnabled                 resb 0x001; 0x001c  R		Culling enable.  Note: culling is done in software and is not necessary in the driver 
.poly_SmoothEnabled                   resb 0x001; 0x001d  R		Polygon anti-aliasing enable 
.poly_OffsetPointEnabled              resb 0x001; 0x001e  R		Polygon Offset for Point mode enable 
.poly_OffsetLineEnabled               resb 0x001; 0x001f  R		Polygon Offset for Line mode enable 
.poly_OffsetFillEnabled               resb 0x001; 0x0020  R		Polygon Offset for Fill mode enable 
.poly_StippleEnabled                  resb 0x001; 0x0021  R		Polygon stipple enable 
.padding_022                          resb 0x002 
.light_LightingEnabled                resb 0x001; 0x0024  NA 
.light_ColorMaterialEnabled           resb 0x001; 0x0025  NA 
.padding_026                          resb 0x002 
.light_ColorMaterialFace              resd 0x001; 0x0028  NA 
.light_ColorMaterialParam             resd 0x001; 0x002c  NA 
.light_ShadingModel                   resd 0x001; 0x0030  R		Flat or smooth triangle shading 
.light_AmbientLightColor_R            resd 0x001; 0x0034
.light_AmbientLightColor_G            resd 0x001; 0x0038
.light_AmbientLightColor_B            resd 0x001; 0x003c
.light_AmbientLightColor_A            resd 0x001; 0x0040
.light_LocalViewerEnabled             resb 0x001; 0x0044  NA 
.light_TwoSidedEnabled                resb 0x001; 0x0045  R		If enabled you may see back side triangles 
.padding_046                          resb 0x002 
.light_material                       resb 0x288; 0x0048  NA	Front & Back 
.light_light                          resb 0x3c0; 0x02d0  NA 
.depth_TestEnabled                    resb 0x001; 0x0690  R		Depth test enable 
.padding_691                          resb 0x003 
.depth_TestFunction                   resd 0x001; 0x0694  R		Depth test function 
.depth_ClearValue                     resd 0x001; 0x0698  R		Depth buffer clear value 
.depth_WriteEnabled                   resb 0x001; 0x069c  R		Depth test write enable 
.padding_69d                          resb 0x003 
.color_RedWriteEnabled                resb 0x001; 0x06a0  R		Red Component write enable 
.color_GreenWriteEnabled              resb 0x001; 0x06a1  R		Green Component write enable 
.color_BlueWriteEnabled               resb 0x001; 0x06a2  R		Blue Component write enable 
.color_AlphaWriteEnabled              resb 0x001; 0x06a3  R		Alpha Component write enable 
.color_ClearValue_R                   resd 0x001; 0x06a4
.color_ClearValue_G                   resd 0x001; 0x06a8
.color_ClearValue_B                   resd 0x001; 0x06ac
.color_ClearValue_A                   resd 0x001; 0x06b0
.color_BlendEnabled                   resb 0x001; 0x06b4  R		Color blending enable 
.padding_6b5                          resb 0x003 
.color_BlendSrcFunction               resd 0x001; 0x06b8  R		Color blending source function 
.color_BlendDestFunction              resd 0x001; 0x06bc  R		Color blending destination function 
.color_LogicOp                        resd 0x001; 0x06c0  R		Color buffer logical operation 
.color_LogicOpEnabled                 resb 0x001; 0x06c4  R		Logical operation enable 
.color_DitherEnabled                  resb 0x001; 0x06c5  R		Dithering enable 
.padding_6c6                          resb 0x002 
.stencil_TestEnabled                  resb 0x001; 0x06c8  R		Stencil test enabled 
.padding_6c9                          resb 0x003 
.stencil_ClearValue                   resd 0x001; 0x06cc  R		Stencil clear value 
.stencil_WriteMask                    resd 0x001; 0x06d0  R		Stencil write mask 
.stencil_Function                     resd 0x001; 0x06d4  R		Stencil function 
.stencil_Refrence                     resd 0x001; 0x06d8  R		Stencil refrence value 
.stencil_FunctionMask                 resd 0x001; 0x06dc  R		Stencil function mask 
.stencil_FailOp                       resd 0x001; 0x06e0  R		Stencil Fail Operation 
.stencil_DepthFailOp                  resd 0x001; 0x06e4  R		Stencil depth test fail operation 
.stencil_DepthPassOp                  resd 0x001; 0x06e8  R		Stencil depth test pass operation 
.texture_Bound                        resd 0x018; 0x06ec  R		__GL_NUMBER_OF_TEXTURE_TARGETS * TextureUnits] 
.texture_s                            resb 0x090; 0x074c  R		Texture Gen state per TMU 
.texture_t                            resb 0x090; 0x07dc  R		Texture Gen state per TMU 
.texture_r                            resb 0x090; 0x086c  R		Texture Gen state per TMU 
.texture_q                            resb 0x090; 0x08fc  R		Texture Gen state per TMU 
.texture_SelectedUnit                 resd 0x001; 0x098c  R		Currently selected texture unit 
.texture_Enabled1D                    resb 0x004; 0x0990  R		Texture 1D Enable state per TMU 
.texture_Enabled2D                    resb 0x004; 0x0994  R		Texture 2D Enable state per TMU 
.texture_Enabled3D                    resb 0x004; 0x0998  R		Texture 3D Enable state per TMU 
.texture_EnvMode                      resd 0x004; 0x099c  R 
.texture_EnvColor                     resb 0x040; 0x09ac  R 
.texture_GenEnabled                   resb 0x010; 0x09ec  NA	Texture GenEnable[tmu][coord] 
.xform_Normalize                      resb 0x001; 0x09fc
.padding_9fd                          resb 0x003 
.xform_ClipPlanesMask                 resd 0x001; 0x0a00
.xform_MatrixMode                     resd 0x001; 0x0a04
.xform_EyeClipPlanes                  resb 0x060; 0x0a08
.viewport_X                           resd 0x001; 0x0a68
.viewport_Y                           resd 0x001; 0x0a6c
.viewport_Width                       resd 0x001; 0x0a70
.viewport_Height                      resd 0x001; 0x0a74
.viewport_ZNear                       resd 0x001; 0x0a78
.viewport_ZFar                        resd 0x001; 0x0a7c
.scissor_Enabled                      resb 0x001; 0x0a80  R		Scissors enable 
.padding_a81                          resb 0x003 
.scissor_X                            resd 0x001; 0x0a84  R		Left of scissor region, inclusive 
.scissor_Y                            resd 0x001; 0x0a88  R		Bottom of scissor region, inclusive 
.scissor_Width                        resd 0x001; 0x0a8c  R		Width of scissor region 
.scissor_Height                       resd 0x001; 0x0a90  R		Height of scissor region 
.hint_PerspectiveCorrection           resd 0x001; 0x0a94  R 
.hint_PointSmooth                     resd 0x001; 0x0a98  R 
.hint_LineSmooth                      resd 0x001; 0x0a9c  R 
.hint_PolygonSmooth                   resd 0x001; 0x0aa0  R 
.hint_Fog                             resd 0x001; 0x0aa4  R 
.accum_ClearColor_R                   resd 0x001; 0x0aa8
.accum_ClearColor_G                   resd 0x001; 0x0aac
.accum_ClearColor_B                   resd 0x001; 0x0ab0
.accum_ClearColor_A                   resd 0x001; 0x0ab4
.fog_Color_R                          resd 0x001; 0x0ab8
.fog_Color_G                          resd 0x001; 0x0abc
.fog_Color_B                          resd 0x001; 0x0ac0
.fog_Color_A                          resd 0x001; 0x0ac4
.fog_Enabled                          resb 0x001; 0x0ac8  R		Fogging enabled 
.padding_ac9                          resb 0x003 
.fog_Mode                             resd 0x001; 0x0acc  R		Fog Mode (linear, exp, exp2) 
.fog_Density                          resd 0x001; 0x0ad0  R		Fog density 
.fog_Start                            resd 0x001; 0x0ad4  R		Fog start 
.fog_End                              resd 0x001; 0x0ad8  R		Fog end 
.line_SmoothEnabled                   resb 0x001; 0x0adc  R		Anti-Alaising 
.padding_add                          resb 0x003 
.line_RequestedWidth                  resd 0x001; 0x0ae0  R 
.line_SmoothWidth                     resd 0x001; 0x0ae4  R 
.line_AliasedWidth                    resd 0x001; 0x0ae8  R 
.line_StippleEnabled                  resb 0x001; 0x0aec  R 
.padding_aed                          resb 0x001 
.line_StippleMask                     resw 0x001; 0x0aee  R 
.line_StippleRepeat                   resd 0x001; 0x0af0  R 
.point_SmoothEnabled                  resb 0x001; 0x0af4  R		Anti-Alaising 
.padding_af5                          resb 0x003 
.point_SizeRequested                  resd 0x001; 0x0af8  R 
.point_SmoothSize                     resd 0x001; 0x0afc  R 
.point_AliasedSize                    resd 0x001; 0x0b00  R 
.alpha_TestEnabled                    resb 0x001; 0x0b04  R		 
.padding_b05                          resb 0x003 
.alpha_TestFunction                   resd 0x001; 0x0b08  R 
.alpha_TestValue                      resd 0x001; 0x0b0c  R		Float 0.0 to 1.0 
.current_Normal_X                     resd 0x001; 0x0b10
.current_Normal_Y                     resd 0x001; 0x0b14
.current_Normal_Z                     resd 0x001; 0x0b18
.current_Normal_W                     resd 0x001; 0x0b1c
.current_UserColor_R                  resd 0x001; 0x0b20
.current_UserColor_G                  resd 0x001; 0x0b24
.current_UserColor_B                  resd 0x001; 0x0b28
.current_UserColor_A                  resd 0x001; 0x0b2c
.current_Color_R                      resd 0x001; 0x0b30
.current_Color_G                      resd 0x001; 0x0b34
.current_Color_B                      resd 0x001; 0x0b38
.current_Color_A                      resd 0x001; 0x0b3c
.current_Texture1_X                   resd 0x001; 0x0b40
.current_Texture1_Y                   resd 0x001; 0x0b44
.current_Texture1_Z                   resd 0x001; 0x0b48
.current_Texture1_W                   resd 0x001; 0x0b4c
.current_Texture2_X                   resd 0x001; 0x0b50
.current_Texture2_Y                   resd 0x001; 0x0b54
.current_Texture2_Z                   resd 0x001; 0x0b58
.current_Texture2_W                   resd 0x001; 0x0b5c
.current_Texture3_X                   resd 0x001; 0x0b60
.current_Texture3_Y                   resd 0x001; 0x0b64
.current_Texture3_Z                   resd 0x001; 0x0b68
.current_Texture3_W                   resd 0x001; 0x0b6c
.current_Texture4_X                   resd 0x001; 0x0b70
.current_Texture4_Y                   resd 0x001; 0x0b74
.current_Texture4_Z                   resd 0x001; 0x0b78
.current_Texture4_W                   resd 0x001; 0x0b7c
.current_Edge                         resd 0x001; 0x0b80
.pixel_transferMode_ScaleR            resd 0x001; 0x0b84
.pixel_transferMode_ScaleG            resd 0x001; 0x0b88
.pixel_transferMode_ScaleB            resd 0x001; 0x0b8c
.pixel_transferMode_ScaleA            resd 0x001; 0x0b90
.pixel_transferMode_ScaleD            resd 0x001; 0x0b94
.pixel_transferMode_BiasR             resd 0x001; 0x0b98
.pixel_transferMode_BiasG             resd 0x001; 0x0b9c
.pixel_transferMode_BiasB             resd 0x001; 0x0ba0
.pixel_transferMode_BiasA             resd 0x001; 0x0ba4
.pixel_transferMode_BiasD             resd 0x001; 0x0ba8
.pixel_transferMode_ZoomX             resd 0x001; 0x0bac
.pixel_transferMode_ZoomY             resd 0x001; 0x0bb0
.pixel_transferMode_IndexShift        resd 0x001; 0x0bb4
.pixel_transferMode_IndexOffset       resd 0x001; 0x0bb8
.pixel_transferMode_MapColor          resb 0x001; 0x0bbc
.pixel_transferMode_MapStencil        resb 0x001; 0x0bbd
.padding_bbe                          resb 0x002 
.pixel_packModes_SwapEndian           resb 0x001; 0x0bc0  
.pixel_packModes_LsbFirst             resb 0x001; 0x0bc1
.padding_bc2                          resb 0x002 
.pixel_packModes_LineLength           resd 0x001; 0x0bc4
.pixel_packModes_SkipLines            resd 0x001; 0x0bc8
.pixel_packModes_SkipPixels           resd 0x001; 0x0bcc
.pixel_packModes_Alignment            resd 0x001; 0x0bd0
.pixel_unpackModes_SwapEndian         resb 0x001; 0x0bd4  
.pixel_unpackModes_LsbFirst           resb 0x001; 0x0bd5
.padding_bd6                          resb 0x002 
.pixel_unpackModes_LineLength         resd 0x001; 0x0bd8
.pixel_unpackModes_SkipLines          resd 0x001; 0x0bdc
.pixel_unpackModes_SkipPixels         resd 0x001; 0x0be0
.pixel_unpackModes_Alignment          resd 0x001; 0x0be4
.pixel_pixelMap                       resb 0x050; 0x0be8  R		__GL_N_PIXEL_MAPS 
.pixel_ReadBuffer                     resd 0x001; 0x0c38  R 
.pixel_ReadBufferReturn               resd 0x001; 0x0c3c  R 
.evaluator_u1_Start                   resd 0x001; 0x0c40  
.evaluator_u1_Finish                  resd 0x001; 0x0c44
.evaluator_u1_N                       resd 0x001; 0x0c48
.evaluator_u2_Start                   resd 0x001; 0x0c4c  
.evaluator_u2_Finish                  resd 0x001; 0x0c50
.evaluator_u2_N                       resd 0x001; 0x0c54
.evaluator_v2_Start                   resd 0x001; 0x0c58  
.evaluator_v2_Finish                  resd 0x001; 0x0c5c
.evaluator_v2_N                       resd 0x001; 0x0c60
.evaluator_Map1Enabled                resb 0x009; 0x0c64  __GL_MAP_RANGE_COUNT 
.evaluator_Map2Enabled                resb 0x009; 0x0c6d  __GL_MAP_RANGE_COUNT 
.evaluator_AutonormalEnabled          resb 0x001; 0x0c76
.padding_c77                          resb 0x001 
.list_ListBase                        resd 0x001; 0x0c78
.vertexArray_SelectedTextureUnit       resd 0x001; 0x0c7c
.vertexArray_VertexPtr                resd 0x001; 0x0c80  
.vertexArray_VertexSize               resd 0x001; 0x0c84
.vertexArray_VertexType               resd 0x001; 0x0c88
.vertexArray_VertexStride             resd 0x001; 0x0c8c
.vertexArray_NormalPtr                resd 0x001; 0x0c90
.vertexArray_NormalType               resd 0x001; 0x0c94
.vertexArray_NormalStride             resd 0x001; 0x0c98
.vertexArray_ColorPtr                 resd 0x001; 0x0c9c
.vertexArray_ColorSize                resd 0x001; 0x0ca0
.vertexArray_ColorType                resd 0x001; 0x0ca4
.vertexArray_ColorStride              resd 0x001; 0x0ca8
.vertexArray_IndexPtr                 resd 0x001; 0x0cac
.vertexArray_IndexType                resd 0x001; 0x0cb0
.vertexArray_IndexStride              resd 0x001; 0x0cb4  
.vertexArray_TexCoordPtr              resd 0x004; 0x0cb8
.vertexArray_TexCoordSize             resd 0x004; 0x0cc8
.vertexArray_TexCoordType             resd 0x004; 0x0cd8
.vertexArray_TexCoordStride           resd 0x004; 0x0ce8
.vertexArray_EdgeFlagPtr              resd 0x001; 0x0cf8
.vertexArray_EdgeFlagStride           resd 0x001; 0x0cfc
.vertexArray_VertexArrayEnabled       resb 0x001; 0x0d00
.vertexArray_NormalArrayEnabled       resb 0x001; 0x0d01
.vertexArray_ColorArrayEnabled        resb 0x001; 0x0d02
.vertexArray_IndexArrayEnabled        resb 0x001; 0x0d03
.vertexArray_TexCoordArrayEnabled       resb 0x004; 0x0d04
.vertexArray_EdgeFlagArrayEnabled       resb 0x001; 0x0d08  
.padding_d09                          resb 0x003 
.opt_UseTempColor                     resb 0x001; 0x0d0c  NA 
.opt_UseTempTex                       resb 0x004; 0x0d0d  NA 
.opt_UseTempNormal                    resb 0x001; 0x0d11  NA 
.opt_UseTempEdge                      resb 0x001; 0x0d12  NA 
.opt_Tex2                             resb 0x004; 0x0d13  R		Per TMU, when set all texture coords R=0, W=1 
.opt_Tex3                             resb 0x004; 0x0d17  R		Per TMU, when set all texture coords W=1 
.padding_d1b                          resb 0x001 
.polyStippleMask                      resb 0x080; 0x0d1c  R		Poloygon stipple mask 
.drawBuffer                           resd 0x001; 0x0d9c  R		Current drawing buffer 
.drawBufferReturn                     resd 0x001; 0x0da0  NA 
.transformClipY0                      resd 0x001; 0x0da4
.transformClipY1                      resd 0x001; 0x0da8
.transformClipX0                      resd 0x001; 0x0dac
.transformClipX1                      resd 0x001; 0x0db0  
.padding_db4                          resb 0x00c 
ENDSTRUC 

%define SIZEOF___glViewportMachine 0x70
STRUC __glViewportMachine                            
.ScaleX                               resd 0x004; 0x0000  R		Scale factor applied after perspective divide.  All four contain same data on PIII otherwize only [0] is valid 
.ScaleY                               resd 0x004; 0x0010  R		Scale factor applied after perspective divide.  All four contain same data on PIII otherwize only [0] is valid 
.ScaleZ                               resd 0x004; 0x0020  R		Scale factor applied after perspective divide.  All four contain same data on PIII otherwize only [0] is valid 
.CenterX                              resd 0x004; 0x0030  R		Offset factor applied after perspective divide.  All four contain same data on PIII otherwize only [0] is valid 
.CenterY                              resd 0x004; 0x0040  R		Offset factor applied after perspective divide.  All four contain same data on PIII otherwize only [0] is valid 
.CenterZ                              resd 0x004; 0x0050  R		Offset factor applied after perspective divide.  All four contain same data on PIII otherwize only [0] is valid 
.BoundsX1                             resd 0x001; 0x0060  R		Screenspace lower X bound, inclusive 
.BoundsX2                             resd 0x001; 0x0064  R		Screenspace upper X bound, exclusive 
.BoundsY1                             resd 0x001; 0x0068  R		Screenspace lower Y bound, inclusive 
.BoundsY2                             resd 0x001; 0x006c  R		Screenspace upper Y bound, exclusive 
ENDSTRUC 

%define SIZEOF_matrix4x4 0x40
STRUC matrix4x4                                      ;  Currently not used by the driver, Will be used for T&L cards latter 
.M00                                  resd 0x001; 0x0000  
.M01                                  resd 0x001; 0x0004
.M02                                  resd 0x001; 0x0008
.M03                                  resd 0x001; 0x000c
.M10                                  resd 0x001; 0x0010
.M11                                  resd 0x001; 0x0014
.M12                                  resd 0x001; 0x0018
.M13                                  resd 0x001; 0x001c
.M20                                  resd 0x001; 0x0020
.M21                                  resd 0x001; 0x0024
.M22                                  resd 0x001; 0x0028
.M23                                  resd 0x001; 0x002c
.M30                                  resd 0x001; 0x0030
.M31                                  resd 0x001; 0x0034
.M32                                  resd 0x001; 0x0038
.M33                                  resd 0x001; 0x003c  
ENDSTRUC 

%define SIZEOF___glMatrixSIMD 0x100
STRUC __glMatrixSIMD                                 ;  Currently not used by the driver, Will be used for T&L cards latter 
.M00                                  resd 0x004; 0x0000  
.M01                                  resd 0x004; 0x0010
.M02                                  resd 0x004; 0x0020
.M03                                  resd 0x004; 0x0030
.M10                                  resd 0x004; 0x0040
.M11                                  resd 0x004; 0x0050
.M12                                  resd 0x004; 0x0060
.M13                                  resd 0x004; 0x0070
.M20                                  resd 0x004; 0x0080
.M21                                  resd 0x004; 0x0090
.M22                                  resd 0x004; 0x00a0
.M23                                  resd 0x004; 0x00b0
.M30                                  resd 0x004; 0x00c0
.M31                                  resd 0x004; 0x00d0
.M32                                  resd 0x004; 0x00e0
.M33                                  resd 0x004; 0x00f0  
ENDSTRUC 

%define SIZEOF___glLightSourceMachine 0x130
STRUC __glLightSourceMachine                         ;  Currently not used by the driver, Will be used for T&L cards latter 
.AmbientR                             resd 0x004; 0x0000
.AmbientG                             resd 0x004; 0x0010  
.AmbientB                             resd 0x004; 0x0020
.SpecularR                            resd 0x004; 0x0030
.SpecularG                            resd 0x004; 0x0040
.SpecularB                            resd 0x004; 0x0050
.DiffuseR                             resd 0x004; 0x0060
.DiffuseG                             resd 0x004; 0x0070
.DiffuseB                             resd 0x004; 0x0080
.HatX                                 resd 0x004; 0x0090
.HatY                                 resd 0x004; 0x00a0
.HatZ                                 resd 0x004; 0x00b0
.PpliHatX                             resd 0x004; 0x00c0
.PpliHatY                             resd 0x004; 0x00d0
.PpliHatZ                             resd 0x004; 0x00e0
.ConstantAttenuation                  resd 0x001; 0x00f0
.LinearAttenuation                    resd 0x001; 0x00f4
.QuadraticAttenuation                 resd 0x001; 0x00f8  
.SpotLightExponent                    resd 0x001; 0x00fc
.Position_X                           resd 0x001; 0x0100
.Position_Y                           resd 0x001; 0x0104
.Position_Z                           resd 0x001; 0x0108
.Position_W                           resd 0x001; 0x010c
.Direction_X                          resd 0x001; 0x0110
.Direction_Y                          resd 0x001; 0x0114
.Direction_Z                          resd 0x001; 0x0118
.Direction_W                          resd 0x001; 0x011c
.CosCutOffAngle                       resd 0x001; 0x0120
.Attenuation                          resd 0x001; 0x0124
.List                                 resd 0x001; 0x0128
.NoSpot                               resb 0x001; 0x012c  
.padding_12d                          resb 0x003 
ENDSTRUC 

%define SIZEOF___glMaterialMachine 0x10
STRUC __glMaterialMachine                            ;  Currently not used by the driver, Will be used for T&L cards latter 
.SceneColorR                          resd 0x001; 0x0000
.SceneColorG                          resd 0x001; 0x0004
.SceneColorB                          resd 0x001; 0x0008
.SceneColorA                          resd 0x001; 0x000c  
ENDSTRUC 

%define SIZEOF___glLightMachine 0x9d0
STRUC __glLightMachine                               ;  Currently not used by the driver, Will be used for T&L cards latter 
.source                               resb 0x980; 0x0000  __GL_NUMBER_OF_LIGHTS 
.material                             resb 0x020; 0x0980
.sources                              resd 0x001; 0x09a0
.List                                 resd 0x008; 0x09a4
.NumberActive                         resd 0x001; 0x09c4
.UseSlow                              resd 0x001; 0x09c8
.padding_9cc                          resb 0x004 
ENDSTRUC 

%define SIZEOF___glDriverProcs 0x22c
STRUC __glDriverProcs                                ;  The proc table used for communication between GL and the driver.  The driver can set these procs at any time within a call to it.  If a drawing proc is nulled then the driver should call callback_ProcChange afterwards. 
.triangleFillFront                    resd 0x001; 0x0000
.triangleFillFrontOdd3                resd 0x001; 0x0004
.triangleFillFrontOdd1                resd 0x001; 0x0008
.triangleFillFrontEven3               resd 0x001; 0x000c
.triangleFillFrontEven1               resd 0x001; 0x0010
.triangleFillFrontFan3                resd 0x001; 0x0014
.triangleFillFrontFan1                resd 0x001; 0x0018
.triangleFillFrontUnordered           resd 0x001; 0x001c
.triangleFillBack                     resd 0x001; 0x0020
.triangleFillBackOdd3                 resd 0x001; 0x0024
.triangleFillBackOdd1                 resd 0x001; 0x0028
.triangleFillBackEven3                resd 0x001; 0x002c
.triangleFillBackEven1                resd 0x001; 0x0030
.triangleFillBackFan3                 resd 0x001; 0x0034
.triangleFillBackFan1                 resd 0x001; 0x0038
.triangleFillBackUnordered            resd 0x001; 0x003c
.triangleLineFront                    resd 0x001; 0x0040
.triangleLineFrontOdd3                resd 0x001; 0x0044
.triangleLineFrontOdd1                resd 0x001; 0x0048
.triangleLineFrontEven3               resd 0x001; 0x004c
.triangleLineFrontEven1               resd 0x001; 0x0050
.triangleLineFrontFan3                resd 0x001; 0x0054
.triangleLineFrontFan1                resd 0x001; 0x0058
.triangleLineFrontUnordered           resd 0x001; 0x005c
.triangleLineBack                     resd 0x001; 0x0060
.triangleLineBackOdd3                 resd 0x001; 0x0064
.triangleLineBackOdd1                 resd 0x001; 0x0068
.triangleLineBackEven3                resd 0x001; 0x006c
.triangleLineBackEven1                resd 0x001; 0x0070
.triangleLineBackFan3                 resd 0x001; 0x0074
.triangleLineBackFan1                 resd 0x001; 0x0078
.triangleLineBackUnordered            resd 0x001; 0x007c
.trianglePointFront                   resd 0x001; 0x0080
.trianglePointFrontOdd3               resd 0x001; 0x0084
.trianglePointFrontOdd1               resd 0x001; 0x0088
.trianglePointFrontEven3              resd 0x001; 0x008c
.trianglePointFrontEven1              resd 0x001; 0x0090
.trianglePointFrontFan3               resd 0x001; 0x0094
.trianglePointFrontFan1               resd 0x001; 0x0098
.trianglePointFrontUnordered          resd 0x001; 0x009c
.trianglePointBack                    resd 0x001; 0x00a0
.trianglePointBackOdd3                resd 0x001; 0x00a4
.trianglePointBackOdd1                resd 0x001; 0x00a8
.trianglePointBackEven3               resd 0x001; 0x00ac
.trianglePointBackEven1               resd 0x001; 0x00b0
.trianglePointBackFan3                resd 0x001; 0x00b4
.trianglePointBackFan1                resd 0x001; 0x00b8
.trianglePointBackUnordered           resd 0x001; 0x00bc
.line                                 resd 0x001; 0x00c0
.lineLoop                             resd 0x001; 0x00c4
.lineUnordered                        resd 0x001; 0x00c8
.point                                resd 0x001; 0x00cc
.pointUnordered                       resd 0x001; 0x00d0
.depthTestEnable                      resd 0x001; 0x00d4
.depthClear                           resd 0x001; 0x00d8
.depthFunc                            resd 0x001; 0x00dc
.depthMask                            resd 0x001; 0x00e0
.setDepthState                        resd 0x001; 0x00e4
.fogEnable                            resd 0x001; 0x00e8
.fogColor                             resd 0x001; 0x00ec
.setFogState                          resd 0x001; 0x00f0
.alphaTestEnable                      resd 0x001; 0x00f4
.alphaFunc                            resd 0x001; 0x00f8
.blendEnable                          resd 0x001; 0x00fc
.blendFunc                            resd 0x001; 0x0100
.colorClear                           resd 0x001; 0x0104
.colorMask                            resd 0x001; 0x0108
.colorDrawBuffer                      resd 0x001; 0x010c
.setColorState                        resd 0x001; 0x0110
.polyStippleEnable                    resd 0x001; 0x0114
.polyStippleMask                      resd 0x001; 0x0118
.setPolyStippleState                  resd 0x001; 0x011c
.scissorTestEnable                    resd 0x001; 0x0120
.scissorRect                          resd 0x001; 0x0124
.setScissorState                      resd 0x001; 0x0128
.stencilTestEnable                    resd 0x001; 0x012c
.stencilMask                          resd 0x001; 0x0130
.stencilFunc                          resd 0x001; 0x0134
.stencilOp                            resd 0x001; 0x0138
.stencilClear                         resd 0x001; 0x013c
.setStencilState                      resd 0x001; 0x0140
.textureEnable                        resd 0x001; 0x0144
.textureSWrapMode                     resd 0x001; 0x0148
.textureTWrapMode                     resd 0x001; 0x014c
.textureMinFilter                     resd 0x001; 0x0150
.textureMagFilter                     resd 0x001; 0x0154
.textureBorderColor                   resd 0x001; 0x0158
.textureEnvMode                       resd 0x001; 0x015c
.textureEnvColor                      resd 0x001; 0x0160
.setTextureState                      resd 0x001; 0x0164
.textureSelect                        resd 0x001; 0x0168
.textureDelete                        resd 0x001; 0x016c
.textureProxyGetType1D                resd 0x001; 0x0170
.textureProxyGetType2D                resd 0x001; 0x0174
.textureProxyGetType3D                resd 0x001; 0x0178
.textureGetType1D                     resd 0x001; 0x017c
.textureGetType2D                     resd 0x001; 0x0180
.textureGetType3D                     resd 0x001; 0x0184
.textureImage1D                       resd 0x001; 0x0188
.textureImage2D                       resd 0x001; 0x018c
.textureImage3D                       resd 0x001; 0x0190
.textureSubImage1D                    resd 0x001; 0x0194
.textureSubImage2D                    resd 0x001; 0x0198
.textureSubImage3D                    resd 0x001; 0x019c
.textureExtractPixel1D                resd 0x001; 0x01a0
.textureExtractPixel2D                resd 0x001; 0x01a4
.textureExtractPixel3D                resd 0x001; 0x01a8
.textureIsResident                    resd 0x001; 0x01ac
.shutdown                             resd 0x001; 0x01b0
.viewportCreate                       resd 0x001; 0x01b4
.viewportDestroy                      resd 0x001; 0x01b8
.bufferClear                          resd 0x001; 0x01bc
.bufferSwap                           resd 0x001; 0x01c0
.bufferLock                           resd 0x001; 0x01c4
.bufferUnlock                         resd 0x001; 0x01c8
.bufferLoadScanline                   resd 0x001; 0x01cc
.bufferStoreScanline                  resd 0x001; 0x01d0
.bufferVerifyMode                     resd 0x001; 0x01d4
.flush                                resd 0x001; 0x01d8
.finish                               resd 0x001; 0x01dc
.polySmoothEnabled                    resd 0x001; 0x01e0
.polyOffset                           resd 0x001; 0x01e4
.polyOffsetFillEnable                 resd 0x001; 0x01e8
.polyOffsetLineEnable                 resd 0x001; 0x01ec
.polyOffsetPointEnable                resd 0x001; 0x01f0
.SetPolyState                         resd 0x001; 0x01f4
.SetLineWidth                         resd 0x001; 0x01f8
.SetPointSize                         resd 0x001; 0x01fc
.resetRasterProcs                     resd 0x001; 0x0200
.setShadeMode                         resd 0x001; 0x0204
.roundZValue                          resd 0x001; 0x0208
.abort                                resd 0x001; 0x020c  Called to abort any rendering in progress.  Engine should be idle before returning. 
.lockClipList                         resd 0x001; 0x0210
.unlockClipList                       resd 0x001; 0x0214
.processThreadEvent                   resd 0x001; 0x0218  Called as a result of releasing the thread sem.  Can potentially be called more often. 
.callback_StoreFrontScanline          resd 0x001; 0x021c  R	Callback for storing the front scanline if the driver cannot copy the front buffer to the frame buffer for some reason. 
.callback_ProcChange                  resd 0x001; 0x0220  R		Callback for the driver to notify GL that one or more of the drawing procs  
.callback_GetOffsetBias               resd 0x001; 0x0224  R Callback to calculate the offset for a triangle.  Figured for 32bit float Z buffer using range 0 to 1 
.callback_Perform                     resd 0x001; 0x0228  R Callback to cause libGL2 to perform one or more tasks.  See the defines. 
ENDSTRUC 

%define SIZEOF___glClipRect 0x10
STRUC __glClipRect                                   
.Left                                 resd 0x001; 0x0000  
.Top                                  resd 0x001; 0x0004
.Right                                resd 0x001; 0x0008
.Bottom                               resd 0x001; 0x000c
ENDSTRUC 

%define SIZEOF___glClipInfoStruct 0x3c
STRUC __glClipInfoStruct                             ;  Clone of the DirectWindow structure.  Treat as Read-Only. Simplified for ASM. 
.LocX                                 resd 0x001; 0x0000  R		Location of the left edge of the front buffer (in Be Screen coordinates) 
.LocY                                 resd 0x001; 0x0004  R		Location of the top edge of the front buffer (in Be Screen coordinates) 
.connected                            resb 0x001; 0x0008  R		Flag indicating if the front buffer is currently enabled for HW acceleration 
.bDirectFormat                        resb 0x001; 0x0009  R 
.padding_00a                          resb 0x002 
.frameBuffer                          resd 0x001; 0x000c  R 
.bytes_per_row                        resd 0x001; 0x0010  R 
.bits_per_pixel                       resd 0x001; 0x0014  R 
.width                                resd 0x001; 0x0018  R 
.height                               resd 0x001; 0x001c  R 
.clip_count                           resd 0x001; 0x0020  R		Number of clip rects 
.clips_allocated                      resd 0x001; 0x0024  NA	 
.pixel_format                         resd 0x001; 0x0028  NA 
.crl_Left                             resd 0x001; 0x002c  
.crl_Top                              resd 0x001; 0x0030
.crl_Right                            resd 0x001; 0x0034
.crl_Bottom                           resd 0x001; 0x0038
ENDSTRUC 

%define SIZEOF___glHashMapBucket 0x38
STRUC __glHashMapBucket                              
.ptrs                                 resd 0x006; 0x0000  __GL_BUCKET_SIZE 
.keys                                 resd 0x006; 0x0018  __GL_BUCKET_SIZE 
.previous                             resd 0x001; 0x0030
.next                                 resd 0x001; 0x0034
ENDSTRUC 

%define SIZEOF___glHashMap 0x41a0
STRUC __glHashMap                                    
.baseBuckets                          resb 0x41a0; 0x0000  __GL_BUCKET_COUNT 
ENDSTRUC 

%define SIZEOF___glFragment 0x2c
STRUC __glFragment                                   
.color_R                              resd 0x001; 0x0000
.color_G                              resd 0x001; 0x0004
.color_B                              resd 0x001; 0x0008
.color_A                              resd 0x001; 0x000c
.x                                    resd 0x001; 0x0010
.y                                    resd 0x001; 0x0014
.z                                    resd 0x001; 0x0018
.s                                    resd 0x001; 0x001c
.t                                    resd 0x001; 0x0020
.qw                                   resd 0x001; 0x0024
.f                                    resd 0x001; 0x0028  
ENDSTRUC 

%define SIZEOF___glBitmap 0x18
STRUC __glBitmap                                     
.width                                resd 0x001; 0x0000
.height                               resd 0x001; 0x0004
.Xbo                                  resd 0x001; 0x0008
.Ybo                                  resd 0x001; 0x000c
.Xbi                                  resd 0x001; 0x0010
.Ybi                                  resd 0x001; 0x0014  
ENDSTRUC 

%define SIZEOF___glShade 0xe4
STRUC __glShade                                      
.mmxDB                                resw 0x001; 0x0000
.mmxDG                                resw 0x001; 0x0002
.mmxDR                                resw 0x001; 0x0004
.mmxDA                                resw 0x001; 0x0006
.xLeft                                resd 0x001; 0x0008
.xRight                               resd 0x001; 0x000c
.xLeftFixed                           resd 0x001; 0x0010  
.xRightFixed                          resd 0x001; 0x0014
.dxdyLeft                             resd 0x001; 0x0018
.dxdyRight                            resd 0x001; 0x001c
.yBottom                              resd 0x001; 0x0020
.yTop                                 resd 0x001; 0x0024
.dy                                   resd 0x001; 0x0028
.iyBottom                             resd 0x001; 0x002c
.iyTop                                resd 0x001; 0x0030
.area                                 resd 0x001; 0x0034
.dxAC                                 resd 0x001; 0x0038  
.dxBC                                 resd 0x001; 0x003c
.dyAC                                 resd 0x001; 0x0040
.dyBC                                 resd 0x001; 0x0044
.dxdyLeftFixed                        resd 0x001; 0x0048
.dxdyRightFixed                       resd 0x001; 0x004c
.r0                                   resd 0x001; 0x0050
.g0                                   resd 0x001; 0x0054
.b0                                   resd 0x001; 0x0058
.a0                                   resd 0x001; 0x005c
.drdx                                 resd 0x001; 0x0060
.dgdx                                 resd 0x001; 0x0064  
.dbdx                                 resd 0x001; 0x0068
.dadx                                 resd 0x001; 0x006c
.drdy                                 resd 0x001; 0x0070
.dgdy                                 resd 0x001; 0x0074
.dbdy                                 resd 0x001; 0x0078
.dady                                 resd 0x001; 0x007c
.drdxdy                               resd 0x001; 0x0080
.dgdxdy                               resd 0x001; 0x0084
.dbdxdy                               resd 0x001; 0x0088
.dadxdy                               resd 0x001; 0x008c  
.z0                                   resd 0x001; 0x0090
.dzdy                                 resd 0x001; 0x0094
.dzdx                                 resd 0x001; 0x0098
.dzdxdy                               resd 0x001; 0x009c
.s0                                   resd 0x001; 0x00a0
.t0                                   resd 0x001; 0x00a4
.qw0                                  resd 0x001; 0x00a8
.dsdx                                 resd 0x001; 0x00ac
.dtdx                                 resd 0x001; 0x00b0
.dqwdx                                resd 0x001; 0x00b4
.dsdy                                 resd 0x001; 0x00b8
.dtdy                                 resd 0x001; 0x00bc
.dqwdy                                resd 0x001; 0x00c0
.dsdxdy                               resd 0x001; 0x00c4
.dtdxdy                               resd 0x001; 0x00c8
.dqwdxdy                              resd 0x001; 0x00cc 	 
.f0                                   resd 0x001; 0x00d0
.dfdy                                 resd 0x001; 0x00d4
.dfdx                                 resd 0x001; 0x00d8
.dfdxdy                               resd 0x001; 0x00dc  
.ccw                                  resb 0x001; 0x00e0
.padding_0e1                          resb 0x003 
ENDSTRUC 

%define SIZEOF___glMethods 0x24
STRUC __glMethods                                    
.ec1                                  resd 0x001; 0x0000
.ec2                                  resd 0x001; 0x0004
.matValidate                          resd 0x001; 0x0008
.bitmap                               resd 0x001; 0x000c
.renderBitmap                         resd 0x001; 0x0010
.lineClipParam                        resd 0x001; 0x0014
.readPixels                           resd 0x001; 0x0018
.fogPoint                             resd 0x001; 0x001c
.error                                resd 0x001; 0x0020
ENDSTRUC 

%define SIZEOF___glAttribute 0xdd0
STRUC __glAttribute                                  
.mask                                 resd 0x001; 0x0000  
.padding_004                          resb 0x00c 
.state_poly_FrontFaceDirection        resd 0x001; 0x0010  R		Winding direction for the fron of a triangle.  GL_CW or GL_CCW 
.state_poly_FrontMode                 resd 0x001; 0x0014  R		Drawing mode for the front of a triangle.  GL_FILL, GL_LINE, GL_POINT 
.state_poly_BackMode                  resd 0x001; 0x0018  R		Drawing mode for the back of a triangle.  GL_FILL, GL_LINE, GL_POINT 
.state_poly_Cull                      resd 0x001; 0x001c  R		Culling mode.  GL_FRONT, GL_BACK, GL_FRON_AND_BACK 
.state_poly_OffsetFactor              resd 0x001; 0x0020  R		Polygon offset factor 
.state_poly_OffsetUnit                resd 0x001; 0x0024  R		Polygon offset unit 
.state_poly_OffsetR                   resd 0x001; 0x0028  NA 
.state_poly_CullFaceEnabled           resb 0x001; 0x002c  R		Culling enable.  Note: culling is done in software and is not necessary in the driver 
.state_poly_SmoothEnabled             resb 0x001; 0x002d  R		Polygon anti-aliasing enable 
.state_poly_OffsetPointEnabled        resb 0x001; 0x002e  R		Polygon Offset for Point mode enable 
.state_poly_OffsetLineEnabled         resb 0x001; 0x002f  R		Polygon Offset for Line mode enable 
.state_poly_OffsetFillEnabled         resb 0x001; 0x0030  R		Polygon Offset for Fill mode enable 
.state_poly_StippleEnabled            resb 0x001; 0x0031  R		Polygon stipple enable 
.padding_032                          resb 0x002 
.state_light_LightingEnabled          resb 0x001; 0x0034  NA 
.state_light_ColorMaterialEnabled       resb 0x001; 0x0035  NA 
.padding_036                          resb 0x002 
.state_light_ColorMaterialFace        resd 0x001; 0x0038  NA 
.state_light_ColorMaterialParam       resd 0x001; 0x003c  NA 
.state_light_ShadingModel             resd 0x001; 0x0040  R		Flat or smooth triangle shading 
.state_light_AmbientLightColor_R       resd 0x001; 0x0044
.state_light_AmbientLightColor_G       resd 0x001; 0x0048
.state_light_AmbientLightColor_B       resd 0x001; 0x004c
.state_light_AmbientLightColor_A       resd 0x001; 0x0050
.state_light_LocalViewerEnabled       resb 0x001; 0x0054  NA 
.state_light_TwoSidedEnabled          resb 0x001; 0x0055  R		If enabled you may see back side triangles 
.padding_056                          resb 0x002 
.state_light_material                 resb 0x288; 0x0058  NA	Front & Back 
.state_light_light                    resb 0x3c0; 0x02e0  NA 
.state_depth_TestEnabled              resb 0x001; 0x06a0  R		Depth test enable 
.padding_6a1                          resb 0x003 
.state_depth_TestFunction             resd 0x001; 0x06a4  R		Depth test function 
.state_depth_ClearValue               resd 0x001; 0x06a8  R		Depth buffer clear value 
.state_depth_WriteEnabled             resb 0x001; 0x06ac  R		Depth test write enable 
.padding_6ad                          resb 0x003 
.state_color_RedWriteEnabled          resb 0x001; 0x06b0  R		Red Component write enable 
.state_color_GreenWriteEnabled        resb 0x001; 0x06b1  R		Green Component write enable 
.state_color_BlueWriteEnabled         resb 0x001; 0x06b2  R		Blue Component write enable 
.state_color_AlphaWriteEnabled        resb 0x001; 0x06b3  R		Alpha Component write enable 
.state_color_ClearValue_R             resd 0x001; 0x06b4
.state_color_ClearValue_G             resd 0x001; 0x06b8
.state_color_ClearValue_B             resd 0x001; 0x06bc
.state_color_ClearValue_A             resd 0x001; 0x06c0
.state_color_BlendEnabled             resb 0x001; 0x06c4  R		Color blending enable 
.padding_6c5                          resb 0x003 
.state_color_BlendSrcFunction         resd 0x001; 0x06c8  R		Color blending source function 
.state_color_BlendDestFunction        resd 0x001; 0x06cc  R		Color blending destination function 
.state_color_LogicOp                  resd 0x001; 0x06d0  R		Color buffer logical operation 
.state_color_LogicOpEnabled           resb 0x001; 0x06d4  R		Logical operation enable 
.state_color_DitherEnabled            resb 0x001; 0x06d5  R		Dithering enable 
.padding_6d6                          resb 0x002 
.state_stencil_TestEnabled            resb 0x001; 0x06d8  R		Stencil test enabled 
.padding_6d9                          resb 0x003 
.state_stencil_ClearValue             resd 0x001; 0x06dc  R		Stencil clear value 
.state_stencil_WriteMask              resd 0x001; 0x06e0  R		Stencil write mask 
.state_stencil_Function               resd 0x001; 0x06e4  R		Stencil function 
.state_stencil_Refrence               resd 0x001; 0x06e8  R		Stencil refrence value 
.state_stencil_FunctionMask           resd 0x001; 0x06ec  R		Stencil function mask 
.state_stencil_FailOp                 resd 0x001; 0x06f0  R		Stencil Fail Operation 
.state_stencil_DepthFailOp            resd 0x001; 0x06f4  R		Stencil depth test fail operation 
.state_stencil_DepthPassOp            resd 0x001; 0x06f8  R		Stencil depth test pass operation 
.state_texture_Bound                  resd 0x018; 0x06fc  R		__GL_NUMBER_OF_TEXTURE_TARGETS * TextureUnits] 
.state_texture_s                      resb 0x090; 0x075c  R		Texture Gen state per TMU 
.state_texture_t                      resb 0x090; 0x07ec  R		Texture Gen state per TMU 
.state_texture_r                      resb 0x090; 0x087c  R		Texture Gen state per TMU 
.state_texture_q                      resb 0x090; 0x090c  R		Texture Gen state per TMU 
.state_texture_SelectedUnit           resd 0x001; 0x099c  R		Currently selected texture unit 
.state_texture_Enabled1D              resb 0x004; 0x09a0  R		Texture 1D Enable state per TMU 
.state_texture_Enabled2D              resb 0x004; 0x09a4  R		Texture 2D Enable state per TMU 
.state_texture_Enabled3D              resb 0x004; 0x09a8  R		Texture 3D Enable state per TMU 
.state_texture_EnvMode                resd 0x004; 0x09ac  R 
.state_texture_EnvColor               resb 0x040; 0x09bc  R 
.state_texture_GenEnabled             resb 0x010; 0x09fc  NA	Texture GenEnable[tmu][coord] 
.state_xform_Normalize                resb 0x001; 0x0a0c
.padding_a0d                          resb 0x003 
.state_xform_ClipPlanesMask           resd 0x001; 0x0a10
.state_xform_MatrixMode               resd 0x001; 0x0a14
.state_xform_EyeClipPlanes            resb 0x060; 0x0a18
.state_viewport_X                     resd 0x001; 0x0a78
.state_viewport_Y                     resd 0x001; 0x0a7c
.state_viewport_Width                 resd 0x001; 0x0a80
.state_viewport_Height                resd 0x001; 0x0a84
.state_viewport_ZNear                 resd 0x001; 0x0a88
.state_viewport_ZFar                  resd 0x001; 0x0a8c
.state_scissor_Enabled                resb 0x001; 0x0a90  R		Scissors enable 
.padding_a91                          resb 0x003 
.state_scissor_X                      resd 0x001; 0x0a94  R		Left of scissor region, inclusive 
.state_scissor_Y                      resd 0x001; 0x0a98  R		Bottom of scissor region, inclusive 
.state_scissor_Width                  resd 0x001; 0x0a9c  R		Width of scissor region 
.state_scissor_Height                 resd 0x001; 0x0aa0  R		Height of scissor region 
.state_hint_PerspectiveCorrection       resd 0x001; 0x0aa4  R 
.state_hint_PointSmooth               resd 0x001; 0x0aa8  R 
.state_hint_LineSmooth                resd 0x001; 0x0aac  R 
.state_hint_PolygonSmooth             resd 0x001; 0x0ab0  R 
.state_hint_Fog                       resd 0x001; 0x0ab4  R 
.state_accum_ClearColor_R             resd 0x001; 0x0ab8
.state_accum_ClearColor_G             resd 0x001; 0x0abc
.state_accum_ClearColor_B             resd 0x001; 0x0ac0
.state_accum_ClearColor_A             resd 0x001; 0x0ac4
.state_fog_Color_R                    resd 0x001; 0x0ac8
.state_fog_Color_G                    resd 0x001; 0x0acc
.state_fog_Color_B                    resd 0x001; 0x0ad0
.state_fog_Color_A                    resd 0x001; 0x0ad4
.state_fog_Enabled                    resb 0x001; 0x0ad8  R		Fogging enabled 
.padding_ad9                          resb 0x003 
.state_fog_Mode                       resd 0x001; 0x0adc  R		Fog Mode (linear, exp, exp2) 
.state_fog_Density                    resd 0x001; 0x0ae0  R		Fog density 
.state_fog_Start                      resd 0x001; 0x0ae4  R		Fog start 
.state_fog_End                        resd 0x001; 0x0ae8  R		Fog end 
.state_line_SmoothEnabled             resb 0x001; 0x0aec  R		Anti-Alaising 
.padding_aed                          resb 0x003 
.state_line_RequestedWidth            resd 0x001; 0x0af0  R 
.state_line_SmoothWidth               resd 0x001; 0x0af4  R 
.state_line_AliasedWidth              resd 0x001; 0x0af8  R 
.state_line_StippleEnabled            resb 0x001; 0x0afc  R 
.padding_afd                          resb 0x001 
.state_line_StippleMask               resw 0x001; 0x0afe  R 
.state_line_StippleRepeat             resd 0x001; 0x0b00  R 
.state_point_SmoothEnabled            resb 0x001; 0x0b04  R		Anti-Alaising 
.padding_b05                          resb 0x003 
.state_point_SizeRequested            resd 0x001; 0x0b08  R 
.state_point_SmoothSize               resd 0x001; 0x0b0c  R 
.state_point_AliasedSize              resd 0x001; 0x0b10  R 
.state_alpha_TestEnabled              resb 0x001; 0x0b14  R		 
.padding_b15                          resb 0x003 
.state_alpha_TestFunction             resd 0x001; 0x0b18  R 
.state_alpha_TestValue                resd 0x001; 0x0b1c  R		Float 0.0 to 1.0 
.state_current_Normal_X               resd 0x001; 0x0b20
.state_current_Normal_Y               resd 0x001; 0x0b24
.state_current_Normal_Z               resd 0x001; 0x0b28
.state_current_Normal_W               resd 0x001; 0x0b2c
.state_current_UserColor_R            resd 0x001; 0x0b30
.state_current_UserColor_G            resd 0x001; 0x0b34
.state_current_UserColor_B            resd 0x001; 0x0b38
.state_current_UserColor_A            resd 0x001; 0x0b3c
.state_current_Color_R                resd 0x001; 0x0b40
.state_current_Color_G                resd 0x001; 0x0b44
.state_current_Color_B                resd 0x001; 0x0b48
.state_current_Color_A                resd 0x001; 0x0b4c
.state_current_Texture1_X             resd 0x001; 0x0b50
.state_current_Texture1_Y             resd 0x001; 0x0b54
.state_current_Texture1_Z             resd 0x001; 0x0b58
.state_current_Texture1_W             resd 0x001; 0x0b5c
.state_current_Texture2_X             resd 0x001; 0x0b60
.state_current_Texture2_Y             resd 0x001; 0x0b64
.state_current_Texture2_Z             resd 0x001; 0x0b68
.state_current_Texture2_W             resd 0x001; 0x0b6c
.state_current_Texture3_X             resd 0x001; 0x0b70
.state_current_Texture3_Y             resd 0x001; 0x0b74
.state_current_Texture3_Z             resd 0x001; 0x0b78
.state_current_Texture3_W             resd 0x001; 0x0b7c
.state_current_Texture4_X             resd 0x001; 0x0b80
.state_current_Texture4_Y             resd 0x001; 0x0b84
.state_current_Texture4_Z             resd 0x001; 0x0b88
.state_current_Texture4_W             resd 0x001; 0x0b8c
.state_current_Edge                   resd 0x001; 0x0b90
.state_pixel_transferMode_ScaleR       resd 0x001; 0x0b94
.state_pixel_transferMode_ScaleG       resd 0x001; 0x0b98
.state_pixel_transferMode_ScaleB       resd 0x001; 0x0b9c
.state_pixel_transferMode_ScaleA       resd 0x001; 0x0ba0
.state_pixel_transferMode_ScaleD       resd 0x001; 0x0ba4
.state_pixel_transferMode_BiasR       resd 0x001; 0x0ba8
.state_pixel_transferMode_BiasG       resd 0x001; 0x0bac
.state_pixel_transferMode_BiasB       resd 0x001; 0x0bb0
.state_pixel_transferMode_BiasA       resd 0x001; 0x0bb4
.state_pixel_transferMode_BiasD       resd 0x001; 0x0bb8
.state_pixel_transferMode_ZoomX       resd 0x001; 0x0bbc
.state_pixel_transferMode_ZoomY       resd 0x001; 0x0bc0
.state_pixel_transferMode_IndexShift       resd 0x001; 0x0bc4
.state_pixel_transferMode_IndexOffset       resd 0x001; 0x0bc8
.state_pixel_transferMode_MapColor       resb 0x001; 0x0bcc
.state_pixel_transferMode_MapStencil       resb 0x001; 0x0bcd
.padding_bce                          resb 0x002 
.state_pixel_packModes_SwapEndian       resb 0x001; 0x0bd0  
.state_pixel_packModes_LsbFirst       resb 0x001; 0x0bd1
.padding_bd2                          resb 0x002 
.state_pixel_packModes_LineLength       resd 0x001; 0x0bd4
.state_pixel_packModes_SkipLines       resd 0x001; 0x0bd8
.state_pixel_packModes_SkipPixels       resd 0x001; 0x0bdc
.state_pixel_packModes_Alignment       resd 0x001; 0x0be0
.state_pixel_unpackModes_SwapEndian       resb 0x001; 0x0be4  
.state_pixel_unpackModes_LsbFirst       resb 0x001; 0x0be5
.padding_be6                          resb 0x002 
.state_pixel_unpackModes_LineLength       resd 0x001; 0x0be8
.state_pixel_unpackModes_SkipLines       resd 0x001; 0x0bec
.state_pixel_unpackModes_SkipPixels       resd 0x001; 0x0bf0
.state_pixel_unpackModes_Alignment       resd 0x001; 0x0bf4
.state_pixel_pixelMap                 resb 0x050; 0x0bf8  R		__GL_N_PIXEL_MAPS 
.state_pixel_ReadBuffer               resd 0x001; 0x0c48  R 
.state_pixel_ReadBufferReturn         resd 0x001; 0x0c4c  R 
.state_evaluator_u1_Start             resd 0x001; 0x0c50  
.state_evaluator_u1_Finish            resd 0x001; 0x0c54
.state_evaluator_u1_N                 resd 0x001; 0x0c58
.state_evaluator_u2_Start             resd 0x001; 0x0c5c  
.state_evaluator_u2_Finish            resd 0x001; 0x0c60
.state_evaluator_u2_N                 resd 0x001; 0x0c64
.state_evaluator_v2_Start             resd 0x001; 0x0c68  
.state_evaluator_v2_Finish            resd 0x001; 0x0c6c
.state_evaluator_v2_N                 resd 0x001; 0x0c70
.state_evaluator_Map1Enabled          resb 0x009; 0x0c74  __GL_MAP_RANGE_COUNT 
.state_evaluator_Map2Enabled          resb 0x009; 0x0c7d  __GL_MAP_RANGE_COUNT 
.state_evaluator_AutonormalEnabled       resb 0x001; 0x0c86
.padding_c87                          resb 0x001 
.state_list_ListBase                  resd 0x001; 0x0c88
.state_vertexArray_SelectedTextureUnit       resd 0x001; 0x0c8c
.state_vertexArray_VertexPtr          resd 0x001; 0x0c90  
.state_vertexArray_VertexSize         resd 0x001; 0x0c94
.state_vertexArray_VertexType         resd 0x001; 0x0c98
.state_vertexArray_VertexStride       resd 0x001; 0x0c9c
.state_vertexArray_NormalPtr          resd 0x001; 0x0ca0
.state_vertexArray_NormalType         resd 0x001; 0x0ca4
.state_vertexArray_NormalStride       resd 0x001; 0x0ca8
.state_vertexArray_ColorPtr           resd 0x001; 0x0cac
.state_vertexArray_ColorSize          resd 0x001; 0x0cb0
.state_vertexArray_ColorType          resd 0x001; 0x0cb4
.state_vertexArray_ColorStride        resd 0x001; 0x0cb8
.state_vertexArray_IndexPtr           resd 0x001; 0x0cbc
.state_vertexArray_IndexType          resd 0x001; 0x0cc0
.state_vertexArray_IndexStride        resd 0x001; 0x0cc4  
.state_vertexArray_TexCoordPtr        resd 0x004; 0x0cc8
.state_vertexArray_TexCoordSize       resd 0x004; 0x0cd8
.state_vertexArray_TexCoordType       resd 0x004; 0x0ce8
.state_vertexArray_TexCoordStride       resd 0x004; 0x0cf8
.state_vertexArray_EdgeFlagPtr        resd 0x001; 0x0d08
.state_vertexArray_EdgeFlagStride       resd 0x001; 0x0d0c
.state_vertexArray_VertexArrayEnabled       resb 0x001; 0x0d10
.state_vertexArray_NormalArrayEnabled       resb 0x001; 0x0d11
.state_vertexArray_ColorArrayEnabled       resb 0x001; 0x0d12
.state_vertexArray_IndexArrayEnabled       resb 0x001; 0x0d13
.state_vertexArray_TexCoordArrayEnabled       resb 0x004; 0x0d14
.state_vertexArray_EdgeFlagArrayEnabled       resb 0x001; 0x0d18  
.padding_d19                          resb 0x003 
.state_opt_UseTempColor               resb 0x001; 0x0d1c  NA 
.state_opt_UseTempTex                 resb 0x004; 0x0d1d  NA 
.state_opt_UseTempNormal              resb 0x001; 0x0d21  NA 
.state_opt_UseTempEdge                resb 0x001; 0x0d22  NA 
.state_opt_Tex2                       resb 0x004; 0x0d23  R		Per TMU, when set all texture coords R=0, W=1 
.state_opt_Tex3                       resb 0x004; 0x0d27  R		Per TMU, when set all texture coords W=1 
.padding_d2b                          resb 0x001 
.state_polyStippleMask                resb 0x080; 0x0d2c  R		Poloygon stipple mask 
.state_drawBuffer                     resd 0x001; 0x0dac  R		Current drawing buffer 
.state_drawBufferReturn               resd 0x001; 0x0db0  NA 
.state_transformClipY0                resd 0x001; 0x0db4
.state_transformClipY1                resd 0x001; 0x0db8
.state_transformClipX0                resd 0x001; 0x0dbc
.state_transformClipX1                resd 0x001; 0x0dc0  
.padding_dc4                          resb 0x00c 
ENDSTRUC 

%define SIZEOF___glClientAttribute 0x150
STRUC __glClientAttribute                            
.mask                                 resd 0x001; 0x0000
.pixel_transferMode_ScaleR            resd 0x001; 0x0004
.pixel_transferMode_ScaleG            resd 0x001; 0x0008
.pixel_transferMode_ScaleB            resd 0x001; 0x000c
.pixel_transferMode_ScaleA            resd 0x001; 0x0010
.pixel_transferMode_ScaleD            resd 0x001; 0x0014
.pixel_transferMode_BiasR             resd 0x001; 0x0018
.pixel_transferMode_BiasG             resd 0x001; 0x001c
.pixel_transferMode_BiasB             resd 0x001; 0x0020
.pixel_transferMode_BiasA             resd 0x001; 0x0024
.pixel_transferMode_BiasD             resd 0x001; 0x0028
.pixel_transferMode_ZoomX             resd 0x001; 0x002c
.pixel_transferMode_ZoomY             resd 0x001; 0x0030
.pixel_transferMode_IndexShift        resd 0x001; 0x0034
.pixel_transferMode_IndexOffset       resd 0x001; 0x0038
.pixel_transferMode_MapColor          resb 0x001; 0x003c
.pixel_transferMode_MapStencil        resb 0x001; 0x003d
.padding_03e                          resb 0x002 
.pixel_packModes_SwapEndian           resb 0x001; 0x0040  
.pixel_packModes_LsbFirst             resb 0x001; 0x0041
.padding_042                          resb 0x002 
.pixel_packModes_LineLength           resd 0x001; 0x0044
.pixel_packModes_SkipLines            resd 0x001; 0x0048
.pixel_packModes_SkipPixels           resd 0x001; 0x004c
.pixel_packModes_Alignment            resd 0x001; 0x0050
.pixel_unpackModes_SwapEndian         resb 0x001; 0x0054  
.pixel_unpackModes_LsbFirst           resb 0x001; 0x0055
.padding_056                          resb 0x002 
.pixel_unpackModes_LineLength         resd 0x001; 0x0058
.pixel_unpackModes_SkipLines          resd 0x001; 0x005c
.pixel_unpackModes_SkipPixels         resd 0x001; 0x0060
.pixel_unpackModes_Alignment          resd 0x001; 0x0064
.pixel_pixelMap                       resb 0x050; 0x0068  R		__GL_N_PIXEL_MAPS 
.pixel_ReadBuffer                     resd 0x001; 0x00b8  R 
.pixel_ReadBufferReturn               resd 0x001; 0x00bc  R 
.vertexArray_SelectedTextureUnit       resd 0x001; 0x00c0
.vertexArray_VertexPtr                resd 0x001; 0x00c4  
.vertexArray_VertexSize               resd 0x001; 0x00c8
.vertexArray_VertexType               resd 0x001; 0x00cc
.vertexArray_VertexStride             resd 0x001; 0x00d0
.vertexArray_NormalPtr                resd 0x001; 0x00d4
.vertexArray_NormalType               resd 0x001; 0x00d8
.vertexArray_NormalStride             resd 0x001; 0x00dc
.vertexArray_ColorPtr                 resd 0x001; 0x00e0
.vertexArray_ColorSize                resd 0x001; 0x00e4
.vertexArray_ColorType                resd 0x001; 0x00e8
.vertexArray_ColorStride              resd 0x001; 0x00ec
.vertexArray_IndexPtr                 resd 0x001; 0x00f0
.vertexArray_IndexType                resd 0x001; 0x00f4
.vertexArray_IndexStride              resd 0x001; 0x00f8  
.vertexArray_TexCoordPtr              resd 0x004; 0x00fc
.vertexArray_TexCoordSize             resd 0x004; 0x010c
.vertexArray_TexCoordType             resd 0x004; 0x011c
.vertexArray_TexCoordStride           resd 0x004; 0x012c
.vertexArray_EdgeFlagPtr              resd 0x001; 0x013c
.vertexArray_EdgeFlagStride           resd 0x001; 0x0140
.vertexArray_VertexArrayEnabled       resb 0x001; 0x0144
.vertexArray_NormalArrayEnabled       resb 0x001; 0x0145
.vertexArray_ColorArrayEnabled        resb 0x001; 0x0146
.vertexArray_IndexArrayEnabled        resb 0x001; 0x0147
.vertexArray_TexCoordArrayEnabled       resb 0x004; 0x0148
.vertexArray_EdgeFlagArrayEnabled       resb 0x001; 0x014c  
.padding_14d                          resb 0x003 
ENDSTRUC 

%define SIZEOF___glAttributeMachine 0x88
STRUC __glAttributeMachine                           
.stack                                resd 0x010; 0x0000  __GL_ATTRIB_STACK_DEPTH 
.clientStack                          resd 0x010; 0x0040  __GL_CLIENT_ATTRIB_STACK_DEPTH 
.stackPointer                         resd 0x001; 0x0080
.clientStackPointer                   resd 0x001; 0x0084
ENDSTRUC 

%define SIZEOF___glVertexMachine 0xdc
STRUC __glVertexMachine                              
.MaterialNeeds                        resd 0x001; 0x0000
.TransformGroupCurrent                resd 0x001; 0x0004
.TransformGroup                       resd 0x002; 0x0008
.TransformerCacheAge                  resd 0x010; 0x0010  VAPI_CACHE_SIZE 
.TransformerCacheCode                 resd 0x010; 0x0050  VAPI_CACHE_SIZE 
.TransformerCacheGroup                resd 0x010; 0x0090  VAPI_CACHE_SIZE, Transform code. For glEnd. 
.VapiNeeds                            resd 0x001; 0x00d0
.XformNeeds                           resd 0x001; 0x00d4
.CacheAllocation                      resd 0x001; 0x00d8  
ENDSTRUC 

%define SIZEOF___glEvaluator1 0x10
STRUC __glEvaluator1                                 
.k                                    resd 0x001; 0x0000
.order                                resd 0x001; 0x0004
.u1                                   resd 0x001; 0x0008
.u2                                   resd 0x001; 0x000c  
ENDSTRUC 

%define SIZEOF___glEvaluator2 0x1c
STRUC __glEvaluator2                                 
.k                                    resd 0x001; 0x0000
.majorOrder                           resd 0x001; 0x0004
.minorOrder                           resd 0x001; 0x0008
.u1                                   resd 0x001; 0x000c
.u2                                   resd 0x001; 0x0010
.v1                                   resd 0x001; 0x0014
.v2                                   resd 0x001; 0x0018  
ENDSTRUC 

%define SIZEOF___glEvaluatorMachine 0x1d4
STRUC __glEvaluatorMachine                           
.eval1                                resb 0x090; 0x0000  __GL_MAP_RANGE_COUNT 
.eval2                                resb 0x0fc; 0x0090  __GL_MAP_RANGE_COUNT 
.eval1Data                            resd 0x009; 0x018c  __GL_MAP_RANGE_COUNT 
.eval2Data                            resd 0x009; 0x01b0  __GL_MAP_RANGE_COUNT 
ENDSTRUC 

%define SIZEOF___glMatrix 0x40
STRUC __glMatrix                                     
.matrix                               resd 0x010; 0x0000
ENDSTRUC 

%define SIZEOF___glTransform 0xc4
STRUC __glTransform                                  
.matrix_matrix                        resd 0x010; 0x0000
.inverseTranspose_matrix              resd 0x010; 0x0040
.mvp_matrix                           resd 0x010; 0x0080
.sequence                             resd 0x001; 0x00c0
ENDSTRUC 

%define SIZEOF___glTransformMachine 0x27e8
STRUC __glTransformMachine                           
.maxWindowDimension                   resd 0x001; 0x0000
.modelViewStack                       resb 0x1880; 0x0004  __GL_MODELVIEW_STACK_DEPTH 
.modelView                            resd 0x001; 0x1884
.projectionStack                      resb 0x7a8; 0x1888  __GL_PROJECTION_STACK_DEPTH 
.projection                           resd 0x001; 0x2030
.projectionSequence                   resd 0x001; 0x2034
.textureStack                         resb 0x7a8; 0x2038  __GL_TEXTURE_STACK_DEPTH 
.texture                              resd 0x001; 0x27e0
.matrixIsIdent                        resb 0x001; 0x27e4
.padding_27e5                          resb 0x003 
ENDSTRUC 

%define SIZEOF___glListAllocation 0xc
STRUC __glListAllocation                             
.next                                 resd 0x001; 0x0000
.start                                resd 0x001; 0x0004
.number                               resd 0x001; 0x0008  
ENDSTRUC 

%define SIZEOF___glListItem 0x10
STRUC __glListItem                                   
.size                                 resd 0x001; 0x0000
.space                                resd 0x001; 0x0004
.data                                 resd 0x002; 0x0008  
ENDSTRUC 

%define SIZEOF___glList 0xc
STRUC __glList                                       
.index                                resd 0x001; 0x0000
.next                                 resd 0x001; 0x0004
.listdata                             resd 0x001; 0x0008  
ENDSTRUC 

%define SIZEOF___glListMachineShared 0xc
STRUC __glListMachineShared                          
.hashBuckets                          resd 0x001; 0x0000
.allocated                            resd 0x001; 0x0004
.refcount                             resd 0x001; 0x0008  
ENDSTRUC 

%define SIZEOF___glListMachine 0x14
STRUC __glListMachine                                
.shared                               resd 0x001; 0x0000
.openList                             resd 0x001; 0x0004
.pc                                   resd 0x001; 0x0008
.mode                                 resd 0x001; 0x000c
.nesting                              resd 0x001; 0x0010  
ENDSTRUC 

%define SIZEOF___glFeedbackMachine 0x14
STRUC __glFeedbackMachine                            
.overFlowed                           resb 0x001; 0x0000
.padding_001                          resb 0x003 
.resultBase                           resd 0x001; 0x0004
.result                               resd 0x001; 0x0008
.resultLength                         resd 0x001; 0x000c
.type                                 resd 0x001; 0x0010  
ENDSTRUC 

%define SIZEOF___glLineMachine 0x8
STRUC __glLineMachine                                
.stipplePosition                      resd 0x001; 0x0000
.repeat                               resd 0x001; 0x0004
ENDSTRUC 

%define SIZEOF___glProcTable 0x344
STRUC __glProcTable                                  
.Color3bv                             resd 0x001; 0x0000
.Color3dv                             resd 0x001; 0x0004
.Color3fv                             resd 0x001; 0x0008
.Color3iv                             resd 0x001; 0x000c
.Color3sv                             resd 0x001; 0x0010
.Color3ubv                            resd 0x001; 0x0014
.Color3uiv                            resd 0x001; 0x0018
.Color3usv                            resd 0x001; 0x001c
.Color4bv                             resd 0x001; 0x0020
.Color4dv                             resd 0x001; 0x0024
.Color4fv                             resd 0x001; 0x0028
.Color4iv                             resd 0x001; 0x002c
.Color4sv                             resd 0x001; 0x0030
.Color4ubv                            resd 0x001; 0x0034
.Color4uiv                            resd 0x001; 0x0038
.Color4usv                            resd 0x001; 0x003c
.Normal3fv                            resd 0x001; 0x0040
.TexCoord1fv                          resd 0x001; 0x0044
.TexCoord2fv                          resd 0x001; 0x0048
.TexCoord3fv                          resd 0x001; 0x004c
.TexCoord4fv                          resd 0x001; 0x0050
.Vertex2fv                            resd 0x001; 0x0054
.Vertex3fv                            resd 0x001; 0x0058
.Vertex4fv                            resd 0x001; 0x005c
.Begin                                resd 0x001; 0x0060
.End                                  resd 0x001; 0x0064
.CallList                             resd 0x001; 0x0068
.CallLists                            resd 0x001; 0x006c
.ListBase                             resd 0x001; 0x0070
.Bitmap                               resd 0x001; 0x0074
.EdgeFlag                             resd 0x001; 0x0078
.EdgeFlagv                            resd 0x001; 0x007c
.Indexd                               resd 0x001; 0x0080
.Indexdv                              resd 0x001; 0x0084
.Indexf                               resd 0x001; 0x0088
.Indexfv                              resd 0x001; 0x008c
.Indexi                               resd 0x001; 0x0090
.Indexiv                              resd 0x001; 0x0094
.Indexs                               resd 0x001; 0x0098
.Indexsv                              resd 0x001; 0x009c
.Indexub                              resd 0x001; 0x00a0
.Indexubv                             resd 0x001; 0x00a4
.RasterPos2d                          resd 0x001; 0x00a8
.RasterPos2dv                         resd 0x001; 0x00ac
.RasterPos2f                          resd 0x001; 0x00b0
.RasterPos2fv                         resd 0x001; 0x00b4
.RasterPos2i                          resd 0x001; 0x00b8
.RasterPos2iv                         resd 0x001; 0x00bc
.RasterPos2s                          resd 0x001; 0x00c0
.RasterPos2sv                         resd 0x001; 0x00c4
.RasterPos3d                          resd 0x001; 0x00c8
.RasterPos3dv                         resd 0x001; 0x00cc
.RasterPos3f                          resd 0x001; 0x00d0
.RasterPos3fv                         resd 0x001; 0x00d4
.RasterPos3i                          resd 0x001; 0x00d8
.RasterPos3iv                         resd 0x001; 0x00dc
.RasterPos3s                          resd 0x001; 0x00e0
.RasterPos3sv                         resd 0x001; 0x00e4
.RasterPos4d                          resd 0x001; 0x00e8
.RasterPos4dv                         resd 0x001; 0x00ec
.RasterPos4f                          resd 0x001; 0x00f0
.RasterPos4fv                         resd 0x001; 0x00f4
.RasterPos4i                          resd 0x001; 0x00f8
.RasterPos4iv                         resd 0x001; 0x00fc
.RasterPos4s                          resd 0x001; 0x0100
.RasterPos4sv                         resd 0x001; 0x0104
.Rectd                                resd 0x001; 0x0108
.Rectdv                               resd 0x001; 0x010c
.Rectf                                resd 0x001; 0x0110
.Rectfv                               resd 0x001; 0x0114
.Recti                                resd 0x001; 0x0118
.Rectiv                               resd 0x001; 0x011c
.Rects                                resd 0x001; 0x0120
.Rectsv                               resd 0x001; 0x0124
.ClipPlane                            resd 0x001; 0x0128
.ColorMaterial                        resd 0x001; 0x012c
.CullFace                             resd 0x001; 0x0130
.Fogf                                 resd 0x001; 0x0134
.Fogfv                                resd 0x001; 0x0138
.Fogi                                 resd 0x001; 0x013c
.Fogiv                                resd 0x001; 0x0140
.FrontFace                            resd 0x001; 0x0144
.Hint                                 resd 0x001; 0x0148
.Lightf                               resd 0x001; 0x014c
.Lightfv                              resd 0x001; 0x0150
.Lighti                               resd 0x001; 0x0154
.Lightiv                              resd 0x001; 0x0158
.LightModelf                          resd 0x001; 0x015c
.LightModelfv                         resd 0x001; 0x0160
.LightModeli                          resd 0x001; 0x0164
.LightModeliv                         resd 0x001; 0x0168
.LineStipple                          resd 0x001; 0x016c
.LineWidth                            resd 0x001; 0x0170
.Materialf                            resd 0x001; 0x0174
.Materialfv                           resd 0x001; 0x0178
.Materiali                            resd 0x001; 0x017c
.Materialiv                           resd 0x001; 0x0180
.PointSize                            resd 0x001; 0x0184
.PolygonMode                          resd 0x001; 0x0188
.PolygonStipple                       resd 0x001; 0x018c
.Scissor                              resd 0x001; 0x0190
.ShadeModel                           resd 0x001; 0x0194
.TexParameterf                        resd 0x001; 0x0198
.TexParameterfv                       resd 0x001; 0x019c
.TexParameteri                        resd 0x001; 0x01a0
.TexParameteriv                       resd 0x001; 0x01a4
.TexImage1D                           resd 0x001; 0x01a8
.TexImage2D                           resd 0x001; 0x01ac
.TexEnvf                              resd 0x001; 0x01b0
.TexEnvfv                             resd 0x001; 0x01b4
.TexEnvi                              resd 0x001; 0x01b8
.TexEnviv                             resd 0x001; 0x01bc
.TexGend                              resd 0x001; 0x01c0
.TexGendv                             resd 0x001; 0x01c4
.TexGenf                              resd 0x001; 0x01c8
.TexGenfv                             resd 0x001; 0x01cc
.TexGeni                              resd 0x001; 0x01d0
.TexGeniv                             resd 0x001; 0x01d4
.InitNames                            resd 0x001; 0x01d8
.LoadName                             resd 0x001; 0x01dc
.PassThrough                          resd 0x001; 0x01e0
.PopName                              resd 0x001; 0x01e4
.PushName                             resd 0x001; 0x01e8
.DrawBuffer                           resd 0x001; 0x01ec
.Clear                                resd 0x001; 0x01f0
.ClearAccum                           resd 0x001; 0x01f4
.ClearIndex                           resd 0x001; 0x01f8
.ClearColor                           resd 0x001; 0x01fc
.ClearStencil                         resd 0x001; 0x0200
.ClearDepth                           resd 0x001; 0x0204
.StencilMask                          resd 0x001; 0x0208
.ColorMask                            resd 0x001; 0x020c
.DepthMask                            resd 0x001; 0x0210
.IndexMask                            resd 0x001; 0x0214
.Accum                                resd 0x001; 0x0218
.Disable                              resd 0x001; 0x021c
.Enable                               resd 0x001; 0x0220
.PopAttrib                            resd 0x001; 0x0224
.PushAttrib                           resd 0x001; 0x0228
.Map1d                                resd 0x001; 0x022c
.Map1f                                resd 0x001; 0x0230
.Map2d                                resd 0x001; 0x0234
.Map2f                                resd 0x001; 0x0238
.MapGrid1d                            resd 0x001; 0x023c
.MapGrid1f                            resd 0x001; 0x0240
.MapGrid2d                            resd 0x001; 0x0244
.MapGrid2f                            resd 0x001; 0x0248
.EvalCoord1d                          resd 0x001; 0x024c
.EvalCoord1dv                         resd 0x001; 0x0250
.EvalCoord1f                          resd 0x001; 0x0254
.EvalCoord1fv                         resd 0x001; 0x0258
.EvalCoord2d                          resd 0x001; 0x025c
.EvalCoord2dv                         resd 0x001; 0x0260
.EvalCoord2f                          resd 0x001; 0x0264
.EvalCoord2fv                         resd 0x001; 0x0268
.EvalMesh1                            resd 0x001; 0x026c
.EvalPoint1                           resd 0x001; 0x0270
.EvalMesh2                            resd 0x001; 0x0274
.EvalPoint2                           resd 0x001; 0x0278
.AlphaFunc                            resd 0x001; 0x027c
.BlendFunc                            resd 0x001; 0x0280
.LogicOp                              resd 0x001; 0x0284
.StencilFunc                          resd 0x001; 0x0288
.StencilOp                            resd 0x001; 0x028c
.DepthFunc                            resd 0x001; 0x0290
.PixelZoom                            resd 0x001; 0x0294
.PixelTransferf                       resd 0x001; 0x0298
.PixelTransferi                       resd 0x001; 0x029c
.PixelMapfv                           resd 0x001; 0x02a0
.PixelMapuiv                          resd 0x001; 0x02a4
.PixelMapusv                          resd 0x001; 0x02a8
.ReadBuffer                           resd 0x001; 0x02ac
.CopyPixels                           resd 0x001; 0x02b0
.DrawPixels                           resd 0x001; 0x02b4
.DepthRange                           resd 0x001; 0x02b8
.Frustum                              resd 0x001; 0x02bc
.LoadIdentity                         resd 0x001; 0x02c0
.LoadMatrixf                          resd 0x001; 0x02c4
.LoadMatrixd                          resd 0x001; 0x02c8
.MatrixMode                           resd 0x001; 0x02cc
.MultMatrixf                          resd 0x001; 0x02d0
.MultMatrixd                          resd 0x001; 0x02d4
.Ortho                                resd 0x001; 0x02d8
.PopMatrix                            resd 0x001; 0x02dc
.PushMatrix                           resd 0x001; 0x02e0
.Rotated                              resd 0x001; 0x02e4
.Rotatef                              resd 0x001; 0x02e8
.Scaled                               resd 0x001; 0x02ec
.Scalef                               resd 0x001; 0x02f0
.Translated                           resd 0x001; 0x02f4
.Translatef                           resd 0x001; 0x02f8
.Viewport                             resd 0x001; 0x02fc
.PolygonOffset                        resd 0x001; 0x0300
.ArrayElement                         resd 0x001; 0x0304
.DrawArrays                           resd 0x001; 0x0308
.DrawElements                         resd 0x001; 0x030c
.TexSubImage1D                        resd 0x001; 0x0310
.TexSubImage2D                        resd 0x001; 0x0314
.CopyTexImage1D                       resd 0x001; 0x0318
.CopyTexImage2D                       resd 0x001; 0x031c
.CopyTexSubImage1D                    resd 0x001; 0x0320
.CopyTexSubImage2D                    resd 0x001; 0x0324
.BindTexture                          resd 0x001; 0x0328
.PrioritizeTextures                   resd 0x001; 0x032c
.MultiTexCoord1fvARB                  resd 0x001; 0x0330
.MultiTexCoord2fvARB                  resd 0x001; 0x0334
.MultiTexCoord3fvARB                  resd 0x001; 0x0338
.MultiTexCoord4fvARB                  resd 0x001; 0x033c
.ActiveTextureARB                     resd 0x001; 0x0340
ENDSTRUC 

%define SIZEOF___glSelectMachine 0x220
STRUC __glSelectMachine                              
.hit                                  resb 0x001; 0x0000
.padding_001                          resb 0x003 
.stack                                resd 0x080; 0x0004  __GL_NAME_STACK_DEPTH 
.sp                                   resd 0x001; 0x0204
.overFlowed                           resb 0x001; 0x0208
.padding_209                          resb 0x003 
.resultBase                           resd 0x001; 0x020c
.result                               resd 0x001; 0x0210
.resultLength                         resd 0x001; 0x0214
.hits                                 resd 0x001; 0x0218
.z                                    resd 0x001; 0x021c  
ENDSTRUC 

%define SIZEOF___glVertexArrayMachine 0xa0
STRUC __glVertexArrayMachine                         
.vertexCall                           resd 0x001; 0x0000
.normalCall                           resd 0x001; 0x0004
.colorCall                            resd 0x001; 0x0008
.indexCall                            resd 0x001; 0x000c
.texCoordCall                         resd 0x001; 0x0010
.edgeFlagCall                         resd 0x001; 0x0014
.vertexSkip                           resd 0x001; 0x0018
.normalSkip                           resd 0x001; 0x001c
.colorSkip                            resd 0x001; 0x0020
.indexSkip                            resd 0x001; 0x0024
.texCoordSkip                         resd 0x004; 0x0028
.edgeFlagSkip                         resd 0x001; 0x0038  
.drawElementCodeCache                 resd 0x008; 0x003c  [4096 * 8] 
.drawElementNeeds                     resd 0x008; 0x005c
.drawElementAge                       resd 0x008; 0x007c
.drawElementCurrentNeeds              resd 0x001; 0x009c
ENDSTRUC 

%define SIZEOF___glSoftwareScanlineProcs 0x1c
STRUC __glSoftwareScanlineProcs                      
.scanlineDepth                        resd 0x001; 0x0000
.loadBits                             resd 0x001; 0x0004
.storeBits                            resd 0x001; 0x0008
.valid                                resb 0x001; 0x000c
.maskEnabled                          resb 0x001; 0x000d
.colorWriteEnabled                    resb 0x001; 0x000e
.fastScanline                         resb 0x001; 0x000f
.processorFuncData                    resd 0x001; 0x0010
.processorFunc                        resd 0x001; 0x0014
.processorNeeds                       resd 0x001; 0x0018  
ENDSTRUC 

%define SIZEOF___glValidMachine 0x28
STRUC __glValidMachine                               
.All                                  resd 0x001; 0x0000
.ModelMatrix                          resd 0x001; 0x0004
.ProjectionMatrix                     resd 0x001; 0x0008
.VertexProcs                          resd 0x001; 0x000c
.LightData                            resd 0x001; 0x0010
.PrimProcessor                        resd 0x001; 0x0014
.VapiProcessor                        resd 0x001; 0x0018
.ModelMatrixType                      resd 0x001; 0x001c
.ProjectionMatrixType                 resd 0x001; 0x0020
.MVPMatrixType                        resd 0x001; 0x0024  
ENDSTRUC 

%define SIZEOF___glBufferMachine 0xb8
STRUC __glBufferMachine                              
.ScanlineFB                           resd 0x001; 0x0000  NA	Scanline buffer, holds a color scanline to be written to the HW buffer.  
.ScanlineFBIN                         resd 0x001; 0x0004  NA	Scanline buffer, holds a color scanline read from the HW buffer.  
.ScanlineA                            resd 0x001; 0x0008  NA	Scanline buffer, holds a accumulation buffer scanline read from or to be written to HW. 
.ScanlineZ                            resd 0x001; 0x000c  NA	Scanline buffer, holds a depth buffer scanline read from or to be written to HW 
.ScanlineS                            resd 0x001; 0x0010  NA	Scanline buffer, holds a stencil buffer scanline read from or to be written to HW. 
.ScanlineV                            resd 0x001; 0x0014  NA	Scanline Valid buffer, contains 1s for pixels to be written and 0s for not. 
.ScanlineY                            resd 0x001; 0x0018  R		Scanline buffer, The Y coordinate for the current scanline. 
.Height                               resd 0x001; 0x001c  R		Height of the front buffer in pixels 
.Width                                resd 0x001; 0x0020  R		Width of the front buffer in pixels 
.ColorFront                           resd 0x001; 0x0024  R		Pointer to the softawre front color buffer if pressent. 
.ColorBack                            resd 0x001; 0x0028  R		Pointer to the softawre back color buffer if pressent. 
.Depth                                resd 0x001; 0x002c  R		Pointer to the softawre depth buffer if pressent. 
.Accum                                resd 0x001; 0x0030  R		Pointer to the softawre accumulation buffer if pressent. 
.Stencil                              resd 0x001; 0x0034  R		Pointer to the softawre stencil buffer if pressent. 
.FullScreen                           resd 0x001; 0x0038  R		Flag to indicate if the application has exclusive access to the screen. 
.ColorFrontHardware                   resd 0x001; 0x003c  RW	Front buffer	1=HW  0=Fallback 
.ColorBackEnabled                     resd 0x001; 0x0040  R 
.ColorBackHardware                    resd 0x001; 0x0044  RW	Back buffer	1=HW  0=Fallback 
.DepthEnabled                         resd 0x001; 0x0048  R 
.DepthHardware                        resd 0x001; 0x004c  RW	1=HW  0=Fallback 
.AccumEnabled                         resd 0x001; 0x0050  R 
.AccumHardware                        resd 0x001; 0x0054  RW	1=HW  0=Fallback 
.StencilEnabled                       resd 0x001; 0x0058  R		Flag to indicate if the user specified a stencil buffer be created. 
.StencilHardware                      resd 0x001; 0x005c  RW	1=HW  0=Fallback 
.ColorScale_R                         resd 0x001; 0x0060
.ColorScale_G                         resd 0x001; 0x0064
.ColorScale_B                         resd 0x001; 0x0068
.ColorScale_A                         resd 0x001; 0x006c
.bitsRed                              resd 0x001; 0x0070  RW	Set the bit count in AcceleratorInit 
.bitsGreen                            resd 0x001; 0x0074  RW	Set the bit count in AcceleratorInit 
.bitsBlue                             resd 0x001; 0x0078  RW	Set the bit count in AcceleratorInit 
.bitsAlpha                            resd 0x001; 0x007c  RW	Set the bit count in AcceleratorInit 
.bitsDepth                            resd 0x001; 0x0080  RW	Set the bit count in AcceleratorInit 
.bitsStencil                          resd 0x001; 0x0084  RW	Set the bit count in AcceleratorInit 
.bitsAccumRed                         resd 0x001; 0x0088  RW	Set the bit count in AcceleratorInit 
.bitsAccumGreen                       resd 0x001; 0x008c  RW	Set the bit count in AcceleratorInit 
.bitsAccumBlue                        resd 0x001; 0x0090  RW	Set the bit count in AcceleratorInit 
.bitsAccumAlpha                       resd 0x001; 0x0094  RW	Set the bit count in AcceleratorInit 
.UserColor                            resd 0x001; 0x0098  R 
.UserDepth                            resd 0x001; 0x009c  R 
.UserStencil                          resd 0x001; 0x00a0  R 
.UserAccum                            resd 0x001; 0x00a4  R 
.RefreshRate                          resd 0x001; 0x00a8  R		Refresh rate for fullscreen mode 
.gammaRed                             resd 0x001; 0x00ac  R 
.gammaGreen                           resd 0x001; 0x00b0  R 
.gammaBlue                            resd 0x001; 0x00b4  R 
ENDSTRUC 

%define SIZEOF___glSoftwareMachine 0x4
STRUC __glSoftwareMachine                            
.ProcsCurrent                         resb 0x001; 0x0000
.PathColorEnable                      resb 0x001; 0x0001
.PathDisable                          resb 0x001; 0x0002
.padding_003                          resb 0x001 
ENDSTRUC 

%define SIZEOF___glPrimitiveMachine 0x21c
STRUC __glPrimitiveMachine                           ;  The data used for geomitry processing of primitives. 
.Count                                resd 0x001; 0x0000  Records the next primitive vertex to be processed. 
.GroupProcessor                       resd 0x001; 0x0004  Processor for the beginning or middle of primitive processing. 
.End                                  resd 0x001; 0x0008  Processor for the end of primitive groups that can handle partial SIMD groups. 
.CacheCurrentNeeds                    resd 0x001; 0x000c  The current needs for primitive processing. 
.CacheProcess                         resd 0x00a; 0x0010  The current GroupProcessors for the various primitives. NULL means they need to be looked up or generated. 
.CacheEnd                             resd 0x00a; 0x0038  The current Ends for the various primitives. NULL means they need to be looked up or generated. 
.CacheCode                            resd 0x020; 0x0060  PRIM_CACHE_SIZE, Needs code for cache entry 
.CacheAge                             resd 0x020; 0x00e0  PRIM_CACHE_SIZE, Age of cache entry 
.CacheProcessPtrs                     resd 0x020; 0x0160  PRIM_CACHE_SIZE, Pointer to processing routine past SIMD prefix. 
.CacheAllocation                      resd 0x001; 0x01e0  Pointer to the allocation of memory for the cache. 
.ClippedPolyProcFront                 resd 0x001; 0x01e4  The current unordered triangle proc for front facing triangles. 
.ClippedPolyProcBack                  resd 0x001; 0x01e8  The current unordered triangle proc for back facing triangles. 
.EdgeTag                              resd 0x001; 0x01ec  The current edge tag.  1=Draw edge,  0=Do not draw edge 
.CullAndMask                          resb 0x001; 0x01f0  0x00 = disabled,  0xff=enabled 
.CullXorMask                          resb 0x001; 0x01f1  0x01 = GL_BACK, 0x00=GL_FRONT, 0x10=GL_FRONT_AND_BACK 
.CullCurrentFacing                    resb 0x001; 0x01f2
.FacingXorMask                        resb 0x001; 0x01f3  0x00 = GL_CCW,  0x01=GL_CW 
.Provoking                            resd 0x001; 0x01f4  The provoking vertex for flat shading.  Use to select color. 
.CallSize                             resd 0x001; 0x01f8  The current call point for SIMD vertex processors. 
.FirstVertexInGroup                   resd 0x001; 0x01fc
.CurrentGroupCount                    resd 0x001; 0x0200
.CurrentVertex                        resd 0x001; 0x0204  The vertex that the next call to glVertexNXX will use. 
.StripFlag                            resd 0x001; 0x0208
.ColorScale_R                         resd 0x001; 0x020c
.ColorScale_G                         resd 0x001; 0x0210
.ColorScale_B                         resd 0x001; 0x0214
.ColorScale_A                         resd 0x001; 0x0218
ENDSTRUC 

%define SIZEOF___glSIMDVertex 0x2e0
STRUC __glSIMDVertex                                 
.ObjX                                 resd 0x004; 0x0000
.ObjY                                 resd 0x004; 0x0010
.ObjZ                                 resd 0x004; 0x0020
.ObjW                                 resd 0x004; 0x0030
.ClipX                                resd 0x004; 0x0040
.ClipY                                resd 0x004; 0x0050
.ClipZ                                resd 0x004; 0x0060
.ClipW                                resd 0x004; 0x0070
.Texture1X                            resd 0x004; 0x0080
.Texture1Y                            resd 0x004; 0x0090
.Texture1Z                            resd 0x004; 0x00a0  
.Texture1W                            resd 0x004; 0x00b0
.ColorFrontR                          resd 0x004; 0x00c0
.ColorFrontG                          resd 0x004; 0x00d0
.ColorFrontB                          resd 0x004; 0x00e0
.ColorFrontA                          resd 0x004; 0x00f0
.NormalX                              resd 0x004; 0x0100
.NormalY                              resd 0x004; 0x0110
.NormalZ                              resd 0x004; 0x0120
.WindowX                              resd 0x004; 0x0130
.WindowY                              resd 0x004; 0x0140
.WindowZ                              resd 0x004; 0x0150
.WindowW                              resd 0x004; 0x0160  
.EyeX                                 resd 0x004; 0x0170
.EyeY                                 resd 0x004; 0x0180
.EyeZ                                 resd 0x004; 0x0190
.EyeW                                 resd 0x004; 0x01a0
.ColorBackR                           resd 0x004; 0x01b0
.ColorBackG                           resd 0x004; 0x01c0
.ColorBackB                           resd 0x004; 0x01d0
.ColorBackA                           resd 0x004; 0x01e0
.Texture2X                            resd 0x004; 0x01f0
.Texture2Y                            resd 0x004; 0x0200
.Texture2Z                            resd 0x004; 0x0210
.Texture2W                            resd 0x004; 0x0220  
.Texture3X                            resd 0x004; 0x0230
.Texture3Y                            resd 0x004; 0x0240
.Texture3Z                            resd 0x004; 0x0250
.Texture3W                            resd 0x004; 0x0260
.Texture4X                            resd 0x004; 0x0270
.Texture4Y                            resd 0x004; 0x0280
.Texture4Z                            resd 0x004; 0x0290
.Texture4W                            resd 0x004; 0x02a0
.ClipCode                             resd 0x004; 0x02b0
.vertexBoundaryEdge                   resd 0x004; 0x02c0  
.Has                                  resd 0x004; 0x02d0
ENDSTRUC 

%define SIZEOF___glTextureMachine 0x5a44
STRUC __glTextureMachine                             
.ActiveUnits                          resd 0x001; 0x0000  RW	Texture units available in hardware.  Please initialize in accelerate_init 
.Enabled                              resb 0x004; 0x0004  R		Per texture unit enabled.  Factors in current state such as current texture and texture enables 
.GenProc                              resd 0x004; 0x0008
.lastName                             resd 0x001; 0x0018  NA 
.Objects_baseBuckets                  resb 0x41a0; 0x001c  __GL_BUCKET_COUNT 
.Defaults                             resb 0x1878; 0x41bc  R		__GL_NUMBER_OF_TEXTURE_TARGETS] 
.Active                               resd 0x004; 0x5a34  R		Number of texture units 
ENDSTRUC 

%define SIZEOF___glVerticesMachine 0x2d00
STRUC __glVerticesMachine                            
.ObjX                                 resd 0x024; 0x0000  
.ObjY                                 resd 0x024; 0x0090
.ObjZ                                 resd 0x024; 0x0120
.ObjW                                 resd 0x024; 0x01b0
.ClipX                                resd 0x024; 0x0240
.ClipY                                resd 0x024; 0x02d0
.ClipZ                                resd 0x024; 0x0360
.ClipW                                resd 0x024; 0x03f0
.TextureX                             resd 0x024; 0x0480
.TextureY                             resd 0x024; 0x0510
.TextureZ                             resd 0x024; 0x05a0
.TextureW                             resd 0x024; 0x0630
.FrontColorR                          resd 0x024; 0x06c0
.FrontColorG                          resd 0x024; 0x0750
.FrontColorB                          resd 0x024; 0x07e0
.FrontColorA                          resd 0x024; 0x0870  
.NormalX                              resd 0x024; 0x0900
.NormalY                              resd 0x024; 0x0990
.NormalZ                              resd 0x024; 0x0a20
.WindowX                              resd 0x024; 0x0ab0
.WindowY                              resd 0x024; 0x0b40
.WindowZ                              resd 0x024; 0x0bd0
.WindowW                              resd 0x024; 0x0c60
.EyeX                                 resd 0x024; 0x0cf0
.EyeY                                 resd 0x024; 0x0d80
.EyeZ                                 resd 0x024; 0x0e10
.EyeW                                 resd 0x024; 0x0ea0
.BackColorR                           resd 0x024; 0x0f30
.BackColorG                           resd 0x024; 0x0fc0
.BackColorB                           resd 0x024; 0x1050  
.BackColorA                           resd 0x024; 0x10e0
.Texture2X                            resd 0x024; 0x1170
.Texture2Y                            resd 0x024; 0x1200
.Texture2Z                            resd 0x024; 0x1290
.Texture2W                            resd 0x024; 0x1320
.Texture3X                            resd 0x024; 0x13b0
.Texture3Y                            resd 0x024; 0x1440
.Texture3Z                            resd 0x024; 0x14d0
.Texture3W                            resd 0x024; 0x1560
.Texture4X                            resd 0x024; 0x15f0
.Texture4Y                            resd 0x024; 0x1680
.Texture4Z                            resd 0x024; 0x1710
.Texture4W                            resd 0x024; 0x17a0  
.ClipCode                             resd 0x024; 0x1830
.Edge                                 resd 0x024; 0x18c0
.Has                                  resd 0x024; 0x1950
.FrontAmbientR                        resd 0x024; 0x19e0
.FrontAmbientG                        resd 0x024; 0x1a70
.FrontAmbientB                        resd 0x024; 0x1b00
.FrontAmbientA                        resd 0x024; 0x1b90
.FrontDiffuseR                        resd 0x024; 0x1c20
.FrontDiffuseG                        resd 0x024; 0x1cb0
.FrontDiffuseB                        resd 0x024; 0x1d40
.FrontDiffuseA                        resd 0x024; 0x1dd0
.FrontSpecularR                       resd 0x024; 0x1e60
.FrontSpecularG                       resd 0x024; 0x1ef0
.FrontSpecularB                       resd 0x024; 0x1f80
.FrontSpecularA                       resd 0x024; 0x2010
.FrontSceneR                          resd 0x024; 0x20a0
.FrontSceneG                          resd 0x024; 0x2130
.FrontSceneB                          resd 0x024; 0x21c0
.FrontSceneA                          resd 0x024; 0x2250
.FrontSpecExp                         resd 0x024; 0x22e0
.BackAmbientR                         resd 0x024; 0x2370
.BackAmbientG                         resd 0x024; 0x2400
.BackAmbientB                         resd 0x024; 0x2490
.BackAmbientA                         resd 0x024; 0x2520
.BackDiffuseR                         resd 0x024; 0x25b0
.BackDiffuseG                         resd 0x024; 0x2640
.BackDiffuseB                         resd 0x024; 0x26d0
.BackDiffuseA                         resd 0x024; 0x2760
.BackSpecularR                        resd 0x024; 0x27f0
.BackSpecularG                        resd 0x024; 0x2880
.BackSpecularB                        resd 0x024; 0x2910
.BackSpecularA                        resd 0x024; 0x29a0
.BackSceneR                           resd 0x024; 0x2a30
.BackSceneG                           resd 0x024; 0x2ac0
.BackSceneB                           resd 0x024; 0x2b50
.BackSceneA                           resd 0x024; 0x2be0
.BackSpecExp                          resd 0x024; 0x2c70
ENDSTRUC 

%define SIZEOF___glInfo 0x3c
STRUC __glInfo                                       
.state_h_version                      resd 0x001; 0x0000  R 
.textureMaxS                          resd 0x001; 0x0004  RW 
.textureMaxT                          resd 0x001; 0x0008  RW 
.textureMaxR                          resd 0x001; 0x000c  RW 
.vendor                               resd 0x001; 0x0010  R  
.renderer                             resd 0x001; 0x0014  R 
.version                              resd 0x001; 0x0018  R 
.extensions                           resd 0x001; 0x001c  R 
.hwRenderer                           resd 0x001; 0x0020  RW Defaults to null, set string to name of HW renderer if present 
.hwGeometry                           resd 0x001; 0x0024  RW Defaults to null, set string to name of HW geometry if present 
.comboStrings                         resd 0x003; 0x0028  R  The three strings that are possible for GL_RENDERER 
.debugLock                            resb 0x001; 0x0034  R 
.debugDevices                         resb 0x001; 0x0035  R 
.debugDriver                          resb 0x001; 0x0036  R 
.debugModes                           resb 0x001; 0x0037  R 
.debugOther                           resb 0x001; 0x0038  R 
.debugDisableDCLock                   resb 0x001; 0x0039  R 
.padding_03a                          resb 0x002 
ENDSTRUC 

%define SIZEOF___glWindowState 0x8
STRUC __glWindowState                                ;  Container for window related state. 
.UtilThreadSem                        resd 0x001; 0x0000  R sem_id that triggers the util thread.  Releasing it will trigger a call to processThreadEvent. 
.DirectWindow                         resd 0x001; 0x0004  NA 
ENDSTRUC 

%define SIZEOF___glContext 0xd9c0
STRUC __glContext                                    
.procTable                            resd 0x001; 0x0000
.padding_004                          resb 0x00c 
.vertices_ObjX                        resd 0x024; 0x0010  
.vertices_ObjY                        resd 0x024; 0x00a0
.vertices_ObjZ                        resd 0x024; 0x0130
.vertices_ObjW                        resd 0x024; 0x01c0
.vertices_ClipX                       resd 0x024; 0x0250
.vertices_ClipY                       resd 0x024; 0x02e0
.vertices_ClipZ                       resd 0x024; 0x0370
.vertices_ClipW                       resd 0x024; 0x0400
.vertices_TextureX                    resd 0x024; 0x0490
.vertices_TextureY                    resd 0x024; 0x0520
.vertices_TextureZ                    resd 0x024; 0x05b0
.vertices_TextureW                    resd 0x024; 0x0640
.vertices_FrontColorR                 resd 0x024; 0x06d0
.vertices_FrontColorG                 resd 0x024; 0x0760
.vertices_FrontColorB                 resd 0x024; 0x07f0
.vertices_FrontColorA                 resd 0x024; 0x0880  
.vertices_NormalX                     resd 0x024; 0x0910
.vertices_NormalY                     resd 0x024; 0x09a0
.vertices_NormalZ                     resd 0x024; 0x0a30
.vertices_WindowX                     resd 0x024; 0x0ac0
.vertices_WindowY                     resd 0x024; 0x0b50
.vertices_WindowZ                     resd 0x024; 0x0be0
.vertices_WindowW                     resd 0x024; 0x0c70
.vertices_EyeX                        resd 0x024; 0x0d00
.vertices_EyeY                        resd 0x024; 0x0d90
.vertices_EyeZ                        resd 0x024; 0x0e20
.vertices_EyeW                        resd 0x024; 0x0eb0
.vertices_BackColorR                  resd 0x024; 0x0f40
.vertices_BackColorG                  resd 0x024; 0x0fd0
.vertices_BackColorB                  resd 0x024; 0x1060  
.vertices_BackColorA                  resd 0x024; 0x10f0
.vertices_Texture2X                   resd 0x024; 0x1180
.vertices_Texture2Y                   resd 0x024; 0x1210
.vertices_Texture2Z                   resd 0x024; 0x12a0
.vertices_Texture2W                   resd 0x024; 0x1330
.vertices_Texture3X                   resd 0x024; 0x13c0
.vertices_Texture3Y                   resd 0x024; 0x1450
.vertices_Texture3Z                   resd 0x024; 0x14e0
.vertices_Texture3W                   resd 0x024; 0x1570
.vertices_Texture4X                   resd 0x024; 0x1600
.vertices_Texture4Y                   resd 0x024; 0x1690
.vertices_Texture4Z                   resd 0x024; 0x1720
.vertices_Texture4W                   resd 0x024; 0x17b0  
.vertices_ClipCode                    resd 0x024; 0x1840
.vertices_Edge                        resd 0x024; 0x18d0
.vertices_Has                         resd 0x024; 0x1960
.vertices_FrontAmbientR               resd 0x024; 0x19f0
.vertices_FrontAmbientG               resd 0x024; 0x1a80
.vertices_FrontAmbientB               resd 0x024; 0x1b10
.vertices_FrontAmbientA               resd 0x024; 0x1ba0
.vertices_FrontDiffuseR               resd 0x024; 0x1c30
.vertices_FrontDiffuseG               resd 0x024; 0x1cc0
.vertices_FrontDiffuseB               resd 0x024; 0x1d50
.vertices_FrontDiffuseA               resd 0x024; 0x1de0
.vertices_FrontSpecularR              resd 0x024; 0x1e70
.vertices_FrontSpecularG              resd 0x024; 0x1f00
.vertices_FrontSpecularB              resd 0x024; 0x1f90
.vertices_FrontSpecularA              resd 0x024; 0x2020
.vertices_FrontSceneR                 resd 0x024; 0x20b0
.vertices_FrontSceneG                 resd 0x024; 0x2140
.vertices_FrontSceneB                 resd 0x024; 0x21d0
.vertices_FrontSceneA                 resd 0x024; 0x2260
.vertices_FrontSpecExp                resd 0x024; 0x22f0
.vertices_BackAmbientR                resd 0x024; 0x2380
.vertices_BackAmbientG                resd 0x024; 0x2410
.vertices_BackAmbientB                resd 0x024; 0x24a0
.vertices_BackAmbientA                resd 0x024; 0x2530
.vertices_BackDiffuseR                resd 0x024; 0x25c0
.vertices_BackDiffuseG                resd 0x024; 0x2650
.vertices_BackDiffuseB                resd 0x024; 0x26e0
.vertices_BackDiffuseA                resd 0x024; 0x2770
.vertices_BackSpecularR               resd 0x024; 0x2800
.vertices_BackSpecularG               resd 0x024; 0x2890
.vertices_BackSpecularB               resd 0x024; 0x2920
.vertices_BackSpecularA               resd 0x024; 0x29b0
.vertices_BackSceneR                  resd 0x024; 0x2a40
.vertices_BackSceneG                  resd 0x024; 0x2ad0
.vertices_BackSceneB                  resd 0x024; 0x2b60
.vertices_BackSceneA                  resd 0x024; 0x2bf0
.vertices_BackSpecExp                 resd 0x024; 0x2c80
.mvp_M00                              resd 0x004; 0x2d10  
.mvp_M01                              resd 0x004; 0x2d20
.mvp_M02                              resd 0x004; 0x2d30
.mvp_M03                              resd 0x004; 0x2d40
.mvp_M10                              resd 0x004; 0x2d50
.mvp_M11                              resd 0x004; 0x2d60
.mvp_M12                              resd 0x004; 0x2d70
.mvp_M13                              resd 0x004; 0x2d80
.mvp_M20                              resd 0x004; 0x2d90
.mvp_M21                              resd 0x004; 0x2da0
.mvp_M22                              resd 0x004; 0x2db0
.mvp_M23                              resd 0x004; 0x2dc0
.mvp_M30                              resd 0x004; 0x2dd0
.mvp_M31                              resd 0x004; 0x2de0
.mvp_M32                              resd 0x004; 0x2df0
.mvp_M33                              resd 0x004; 0x2e00  
.model_M00                            resd 0x004; 0x2e10  
.model_M01                            resd 0x004; 0x2e20
.model_M02                            resd 0x004; 0x2e30
.model_M03                            resd 0x004; 0x2e40
.model_M10                            resd 0x004; 0x2e50
.model_M11                            resd 0x004; 0x2e60
.model_M12                            resd 0x004; 0x2e70
.model_M13                            resd 0x004; 0x2e80
.model_M20                            resd 0x004; 0x2e90
.model_M21                            resd 0x004; 0x2ea0
.model_M22                            resd 0x004; 0x2eb0
.model_M23                            resd 0x004; 0x2ec0
.model_M30                            resd 0x004; 0x2ed0
.model_M31                            resd 0x004; 0x2ee0
.model_M32                            resd 0x004; 0x2ef0
.model_M33                            resd 0x004; 0x2f00  
.invModel_M00                         resd 0x004; 0x2f10  
.invModel_M01                         resd 0x004; 0x2f20
.invModel_M02                         resd 0x004; 0x2f30
.invModel_M03                         resd 0x004; 0x2f40
.invModel_M10                         resd 0x004; 0x2f50
.invModel_M11                         resd 0x004; 0x2f60
.invModel_M12                         resd 0x004; 0x2f70
.invModel_M13                         resd 0x004; 0x2f80
.invModel_M20                         resd 0x004; 0x2f90
.invModel_M21                         resd 0x004; 0x2fa0
.invModel_M22                         resd 0x004; 0x2fb0
.invModel_M23                         resd 0x004; 0x2fc0
.invModel_M30                         resd 0x004; 0x2fd0
.invModel_M31                         resd 0x004; 0x2fe0
.invModel_M32                         resd 0x004; 0x2ff0
.invModel_M33                         resd 0x004; 0x3000  
.isRendering                          resd 0x001; 0x3010  1 for immediate mode, 0 for building display list. 
.polyClipParam                        resd 0x001; 0x3014  All args in regs 
.nextClipTemp                         resd 0x001; 0x3018
.asmProc_Light                        resd 0x001; 0x301c
.asmProc_EWNT_Front                   resd 0x001; 0x3020  
.asmProc_EWNT_Back                    resd 0x001; 0x3024
.renderMode                           resd 0x001; 0x3028
.error                                resd 0x001; 0x302c
.auxBuffers                           resd 0x001; 0x3030
.stencilBufferBits                    resd 0x001; 0x3034  
.padding_3038                          resb 0x008 
.state_poly_FrontFaceDirection        resd 0x001; 0x3040  R		Winding direction for the fron of a triangle.  GL_CW or GL_CCW 
.state_poly_FrontMode                 resd 0x001; 0x3044  R		Drawing mode for the front of a triangle.  GL_FILL, GL_LINE, GL_POINT 
.state_poly_BackMode                  resd 0x001; 0x3048  R		Drawing mode for the back of a triangle.  GL_FILL, GL_LINE, GL_POINT 
.state_poly_Cull                      resd 0x001; 0x304c  R		Culling mode.  GL_FRONT, GL_BACK, GL_FRON_AND_BACK 
.state_poly_OffsetFactor              resd 0x001; 0x3050  R		Polygon offset factor 
.state_poly_OffsetUnit                resd 0x001; 0x3054  R		Polygon offset unit 
.state_poly_OffsetR                   resd 0x001; 0x3058  NA 
.state_poly_CullFaceEnabled           resb 0x001; 0x305c  R		Culling enable.  Note: culling is done in software and is not necessary in the driver 
.state_poly_SmoothEnabled             resb 0x001; 0x305d  R		Polygon anti-aliasing enable 
.state_poly_OffsetPointEnabled        resb 0x001; 0x305e  R		Polygon Offset for Point mode enable 
.state_poly_OffsetLineEnabled         resb 0x001; 0x305f  R		Polygon Offset for Line mode enable 
.state_poly_OffsetFillEnabled         resb 0x001; 0x3060  R		Polygon Offset for Fill mode enable 
.state_poly_StippleEnabled            resb 0x001; 0x3061  R		Polygon stipple enable 
.padding_3062                          resb 0x002 
.state_light_LightingEnabled          resb 0x001; 0x3064  NA 
.state_light_ColorMaterialEnabled       resb 0x001; 0x3065  NA 
.padding_3066                          resb 0x002 
.state_light_ColorMaterialFace        resd 0x001; 0x3068  NA 
.state_light_ColorMaterialParam       resd 0x001; 0x306c  NA 
.state_light_ShadingModel             resd 0x001; 0x3070  R		Flat or smooth triangle shading 
.state_light_AmbientLightColor_R       resd 0x001; 0x3074
.state_light_AmbientLightColor_G       resd 0x001; 0x3078
.state_light_AmbientLightColor_B       resd 0x001; 0x307c
.state_light_AmbientLightColor_A       resd 0x001; 0x3080
.state_light_LocalViewerEnabled       resb 0x001; 0x3084  NA 
.state_light_TwoSidedEnabled          resb 0x001; 0x3085  R		If enabled you may see back side triangles 
.padding_3086                          resb 0x002 
.state_light_material                 resb 0x288; 0x3088  NA	Front & Back 
.state_light_light                    resb 0x3c0; 0x3310  NA 
.state_depth_TestEnabled              resb 0x001; 0x36d0  R		Depth test enable 
.padding_36d1                          resb 0x003 
.state_depth_TestFunction             resd 0x001; 0x36d4  R		Depth test function 
.state_depth_ClearValue               resd 0x001; 0x36d8  R		Depth buffer clear value 
.state_depth_WriteEnabled             resb 0x001; 0x36dc  R		Depth test write enable 
.padding_36dd                          resb 0x003 
.state_color_RedWriteEnabled          resb 0x001; 0x36e0  R		Red Component write enable 
.state_color_GreenWriteEnabled        resb 0x001; 0x36e1  R		Green Component write enable 
.state_color_BlueWriteEnabled         resb 0x001; 0x36e2  R		Blue Component write enable 
.state_color_AlphaWriteEnabled        resb 0x001; 0x36e3  R		Alpha Component write enable 
.state_color_ClearValue_R             resd 0x001; 0x36e4
.state_color_ClearValue_G             resd 0x001; 0x36e8
.state_color_ClearValue_B             resd 0x001; 0x36ec
.state_color_ClearValue_A             resd 0x001; 0x36f0
.state_color_BlendEnabled             resb 0x001; 0x36f4  R		Color blending enable 
.padding_36f5                          resb 0x003 
.state_color_BlendSrcFunction         resd 0x001; 0x36f8  R		Color blending source function 
.state_color_BlendDestFunction        resd 0x001; 0x36fc  R		Color blending destination function 
.state_color_LogicOp                  resd 0x001; 0x3700  R		Color buffer logical operation 
.state_color_LogicOpEnabled           resb 0x001; 0x3704  R		Logical operation enable 
.state_color_DitherEnabled            resb 0x001; 0x3705  R		Dithering enable 
.padding_3706                          resb 0x002 
.state_stencil_TestEnabled            resb 0x001; 0x3708  R		Stencil test enabled 
.padding_3709                          resb 0x003 
.state_stencil_ClearValue             resd 0x001; 0x370c  R		Stencil clear value 
.state_stencil_WriteMask              resd 0x001; 0x3710  R		Stencil write mask 
.state_stencil_Function               resd 0x001; 0x3714  R		Stencil function 
.state_stencil_Refrence               resd 0x001; 0x3718  R		Stencil refrence value 
.state_stencil_FunctionMask           resd 0x001; 0x371c  R		Stencil function mask 
.state_stencil_FailOp                 resd 0x001; 0x3720  R		Stencil Fail Operation 
.state_stencil_DepthFailOp            resd 0x001; 0x3724  R		Stencil depth test fail operation 
.state_stencil_DepthPassOp            resd 0x001; 0x3728  R		Stencil depth test pass operation 
.state_texture_Bound                  resd 0x018; 0x372c  R		__GL_NUMBER_OF_TEXTURE_TARGETS * TextureUnits] 
.state_texture_s                      resb 0x090; 0x378c  R		Texture Gen state per TMU 
.state_texture_t                      resb 0x090; 0x381c  R		Texture Gen state per TMU 
.state_texture_r                      resb 0x090; 0x38ac  R		Texture Gen state per TMU 
.state_texture_q                      resb 0x090; 0x393c  R		Texture Gen state per TMU 
.state_texture_SelectedUnit           resd 0x001; 0x39cc  R		Currently selected texture unit 
.state_texture_Enabled1D              resb 0x004; 0x39d0  R		Texture 1D Enable state per TMU 
.state_texture_Enabled2D              resb 0x004; 0x39d4  R		Texture 2D Enable state per TMU 
.state_texture_Enabled3D              resb 0x004; 0x39d8  R		Texture 3D Enable state per TMU 
.state_texture_EnvMode                resd 0x004; 0x39dc  R 
.state_texture_EnvColor               resb 0x040; 0x39ec  R 
.state_texture_GenEnabled             resb 0x010; 0x3a2c  NA	Texture GenEnable[tmu][coord] 
.state_xform_Normalize                resb 0x001; 0x3a3c
.padding_3a3d                          resb 0x003 
.state_xform_ClipPlanesMask           resd 0x001; 0x3a40
.state_xform_MatrixMode               resd 0x001; 0x3a44
.state_xform_EyeClipPlanes            resb 0x060; 0x3a48
.state_viewport_X                     resd 0x001; 0x3aa8
.state_viewport_Y                     resd 0x001; 0x3aac
.state_viewport_Width                 resd 0x001; 0x3ab0
.state_viewport_Height                resd 0x001; 0x3ab4
.state_viewport_ZNear                 resd 0x001; 0x3ab8
.state_viewport_ZFar                  resd 0x001; 0x3abc
.state_scissor_Enabled                resb 0x001; 0x3ac0  R		Scissors enable 
.padding_3ac1                          resb 0x003 
.state_scissor_X                      resd 0x001; 0x3ac4  R		Left of scissor region, inclusive 
.state_scissor_Y                      resd 0x001; 0x3ac8  R		Bottom of scissor region, inclusive 
.state_scissor_Width                  resd 0x001; 0x3acc  R		Width of scissor region 
.state_scissor_Height                 resd 0x001; 0x3ad0  R		Height of scissor region 
.state_hint_PerspectiveCorrection       resd 0x001; 0x3ad4  R 
.state_hint_PointSmooth               resd 0x001; 0x3ad8  R 
.state_hint_LineSmooth                resd 0x001; 0x3adc  R 
.state_hint_PolygonSmooth             resd 0x001; 0x3ae0  R 
.state_hint_Fog                       resd 0x001; 0x3ae4  R 
.state_accum_ClearColor_R             resd 0x001; 0x3ae8
.state_accum_ClearColor_G             resd 0x001; 0x3aec
.state_accum_ClearColor_B             resd 0x001; 0x3af0
.state_accum_ClearColor_A             resd 0x001; 0x3af4
.state_fog_Color_R                    resd 0x001; 0x3af8
.state_fog_Color_G                    resd 0x001; 0x3afc
.state_fog_Color_B                    resd 0x001; 0x3b00
.state_fog_Color_A                    resd 0x001; 0x3b04
.state_fog_Enabled                    resb 0x001; 0x3b08  R		Fogging enabled 
.padding_3b09                          resb 0x003 
.state_fog_Mode                       resd 0x001; 0x3b0c  R		Fog Mode (linear, exp, exp2) 
.state_fog_Density                    resd 0x001; 0x3b10  R		Fog density 
.state_fog_Start                      resd 0x001; 0x3b14  R		Fog start 
.state_fog_End                        resd 0x001; 0x3b18  R		Fog end 
.state_line_SmoothEnabled             resb 0x001; 0x3b1c  R		Anti-Alaising 
.padding_3b1d                          resb 0x003 
.state_line_RequestedWidth            resd 0x001; 0x3b20  R 
.state_line_SmoothWidth               resd 0x001; 0x3b24  R 
.state_line_AliasedWidth              resd 0x001; 0x3b28  R 
.state_line_StippleEnabled            resb 0x001; 0x3b2c  R 
.padding_3b2d                          resb 0x001 
.state_line_StippleMask               resw 0x001; 0x3b2e  R 
.state_line_StippleRepeat             resd 0x001; 0x3b30  R 
.state_point_SmoothEnabled            resb 0x001; 0x3b34  R		Anti-Alaising 
.padding_3b35                          resb 0x003 
.state_point_SizeRequested            resd 0x001; 0x3b38  R 
.state_point_SmoothSize               resd 0x001; 0x3b3c  R 
.state_point_AliasedSize              resd 0x001; 0x3b40  R 
.state_alpha_TestEnabled              resb 0x001; 0x3b44  R		 
.padding_3b45                          resb 0x003 
.state_alpha_TestFunction             resd 0x001; 0x3b48  R 
.state_alpha_TestValue                resd 0x001; 0x3b4c  R		Float 0.0 to 1.0 
.state_current_Normal_X               resd 0x001; 0x3b50
.state_current_Normal_Y               resd 0x001; 0x3b54
.state_current_Normal_Z               resd 0x001; 0x3b58
.state_current_Normal_W               resd 0x001; 0x3b5c
.state_current_UserColor_R            resd 0x001; 0x3b60
.state_current_UserColor_G            resd 0x001; 0x3b64
.state_current_UserColor_B            resd 0x001; 0x3b68
.state_current_UserColor_A            resd 0x001; 0x3b6c
.state_current_Color_R                resd 0x001; 0x3b70
.state_current_Color_G                resd 0x001; 0x3b74
.state_current_Color_B                resd 0x001; 0x3b78
.state_current_Color_A                resd 0x001; 0x3b7c
.state_current_Texture1_X             resd 0x001; 0x3b80
.state_current_Texture1_Y             resd 0x001; 0x3b84
.state_current_Texture1_Z             resd 0x001; 0x3b88
.state_current_Texture1_W             resd 0x001; 0x3b8c
.state_current_Texture2_X             resd 0x001; 0x3b90
.state_current_Texture2_Y             resd 0x001; 0x3b94
.state_current_Texture2_Z             resd 0x001; 0x3b98
.state_current_Texture2_W             resd 0x001; 0x3b9c
.state_current_Texture3_X             resd 0x001; 0x3ba0
.state_current_Texture3_Y             resd 0x001; 0x3ba4
.state_current_Texture3_Z             resd 0x001; 0x3ba8
.state_current_Texture3_W             resd 0x001; 0x3bac
.state_current_Texture4_X             resd 0x001; 0x3bb0
.state_current_Texture4_Y             resd 0x001; 0x3bb4
.state_current_Texture4_Z             resd 0x001; 0x3bb8
.state_current_Texture4_W             resd 0x001; 0x3bbc
.state_current_Edge                   resd 0x001; 0x3bc0
.state_pixel_transferMode_ScaleR       resd 0x001; 0x3bc4
.state_pixel_transferMode_ScaleG       resd 0x001; 0x3bc8
.state_pixel_transferMode_ScaleB       resd 0x001; 0x3bcc
.state_pixel_transferMode_ScaleA       resd 0x001; 0x3bd0
.state_pixel_transferMode_ScaleD       resd 0x001; 0x3bd4
.state_pixel_transferMode_BiasR       resd 0x001; 0x3bd8
.state_pixel_transferMode_BiasG       resd 0x001; 0x3bdc
.state_pixel_transferMode_BiasB       resd 0x001; 0x3be0
.state_pixel_transferMode_BiasA       resd 0x001; 0x3be4
.state_pixel_transferMode_BiasD       resd 0x001; 0x3be8
.state_pixel_transferMode_ZoomX       resd 0x001; 0x3bec
.state_pixel_transferMode_ZoomY       resd 0x001; 0x3bf0
.state_pixel_transferMode_IndexShift       resd 0x001; 0x3bf4
.state_pixel_transferMode_IndexOffset       resd 0x001; 0x3bf8
.state_pixel_transferMode_MapColor       resb 0x001; 0x3bfc
.state_pixel_transferMode_MapStencil       resb 0x001; 0x3bfd
.padding_3bfe                          resb 0x002 
.state_pixel_packModes_SwapEndian       resb 0x001; 0x3c00  
.state_pixel_packModes_LsbFirst       resb 0x001; 0x3c01
.padding_3c02                          resb 0x002 
.state_pixel_packModes_LineLength       resd 0x001; 0x3c04
.state_pixel_packModes_SkipLines       resd 0x001; 0x3c08
.state_pixel_packModes_SkipPixels       resd 0x001; 0x3c0c
.state_pixel_packModes_Alignment       resd 0x001; 0x3c10
.state_pixel_unpackModes_SwapEndian       resb 0x001; 0x3c14  
.state_pixel_unpackModes_LsbFirst       resb 0x001; 0x3c15
.padding_3c16                          resb 0x002 
.state_pixel_unpackModes_LineLength       resd 0x001; 0x3c18
.state_pixel_unpackModes_SkipLines       resd 0x001; 0x3c1c
.state_pixel_unpackModes_SkipPixels       resd 0x001; 0x3c20
.state_pixel_unpackModes_Alignment       resd 0x001; 0x3c24
.state_pixel_pixelMap                 resb 0x050; 0x3c28  R		__GL_N_PIXEL_MAPS 
.state_pixel_ReadBuffer               resd 0x001; 0x3c78  R 
.state_pixel_ReadBufferReturn         resd 0x001; 0x3c7c  R 
.state_evaluator_u1_Start             resd 0x001; 0x3c80  
.state_evaluator_u1_Finish            resd 0x001; 0x3c84
.state_evaluator_u1_N                 resd 0x001; 0x3c88
.state_evaluator_u2_Start             resd 0x001; 0x3c8c  
.state_evaluator_u2_Finish            resd 0x001; 0x3c90
.state_evaluator_u2_N                 resd 0x001; 0x3c94
.state_evaluator_v2_Start             resd 0x001; 0x3c98  
.state_evaluator_v2_Finish            resd 0x001; 0x3c9c
.state_evaluator_v2_N                 resd 0x001; 0x3ca0
.state_evaluator_Map1Enabled          resb 0x009; 0x3ca4  __GL_MAP_RANGE_COUNT 
.state_evaluator_Map2Enabled          resb 0x009; 0x3cad  __GL_MAP_RANGE_COUNT 
.state_evaluator_AutonormalEnabled       resb 0x001; 0x3cb6
.padding_3cb7                          resb 0x001 
.state_list_ListBase                  resd 0x001; 0x3cb8
.state_vertexArray_SelectedTextureUnit       resd 0x001; 0x3cbc
.state_vertexArray_VertexPtr          resd 0x001; 0x3cc0  
.state_vertexArray_VertexSize         resd 0x001; 0x3cc4
.state_vertexArray_VertexType         resd 0x001; 0x3cc8
.state_vertexArray_VertexStride       resd 0x001; 0x3ccc
.state_vertexArray_NormalPtr          resd 0x001; 0x3cd0
.state_vertexArray_NormalType         resd 0x001; 0x3cd4
.state_vertexArray_NormalStride       resd 0x001; 0x3cd8
.state_vertexArray_ColorPtr           resd 0x001; 0x3cdc
.state_vertexArray_ColorSize          resd 0x001; 0x3ce0
.state_vertexArray_ColorType          resd 0x001; 0x3ce4
.state_vertexArray_ColorStride        resd 0x001; 0x3ce8
.state_vertexArray_IndexPtr           resd 0x001; 0x3cec
.state_vertexArray_IndexType          resd 0x001; 0x3cf0
.state_vertexArray_IndexStride        resd 0x001; 0x3cf4  
.state_vertexArray_TexCoordPtr        resd 0x004; 0x3cf8
.state_vertexArray_TexCoordSize       resd 0x004; 0x3d08
.state_vertexArray_TexCoordType       resd 0x004; 0x3d18
.state_vertexArray_TexCoordStride       resd 0x004; 0x3d28
.state_vertexArray_EdgeFlagPtr        resd 0x001; 0x3d38
.state_vertexArray_EdgeFlagStride       resd 0x001; 0x3d3c
.state_vertexArray_VertexArrayEnabled       resb 0x001; 0x3d40
.state_vertexArray_NormalArrayEnabled       resb 0x001; 0x3d41
.state_vertexArray_ColorArrayEnabled       resb 0x001; 0x3d42
.state_vertexArray_IndexArrayEnabled       resb 0x001; 0x3d43
.state_vertexArray_TexCoordArrayEnabled       resb 0x004; 0x3d44
.state_vertexArray_EdgeFlagArrayEnabled       resb 0x001; 0x3d48  
.padding_3d49                          resb 0x003 
.state_opt_UseTempColor               resb 0x001; 0x3d4c  NA 
.state_opt_UseTempTex                 resb 0x004; 0x3d4d  NA 
.state_opt_UseTempNormal              resb 0x001; 0x3d51  NA 
.state_opt_UseTempEdge                resb 0x001; 0x3d52  NA 
.state_opt_Tex2                       resb 0x004; 0x3d53  R		Per TMU, when set all texture coords R=0, W=1 
.state_opt_Tex3                       resb 0x004; 0x3d57  R		Per TMU, when set all texture coords W=1 
.padding_3d5b                          resb 0x001 
.state_polyStippleMask                resb 0x080; 0x3d5c  R		Poloygon stipple mask 
.state_drawBuffer                     resd 0x001; 0x3ddc  R		Current drawing buffer 
.state_drawBufferReturn               resd 0x001; 0x3de0  NA 
.state_transformClipY0                resd 0x001; 0x3de4
.state_transformClipY1                resd 0x001; 0x3de8
.state_transformClipX0                resd 0x001; 0x3dec
.state_transformClipX1                resd 0x001; 0x3df0  
.padding_3df4                          resb 0x00c 
.texture_ActiveUnits                  resd 0x001; 0x3e00  RW	Texture units available in hardware.  Please initialize in accelerate_init 
.texture_Enabled                      resb 0x004; 0x3e04  R		Per texture unit enabled.  Factors in current state such as current texture and texture enables 
.texture_GenProc                      resd 0x004; 0x3e08
.texture_lastName                     resd 0x001; 0x3e18  NA 
.texture_Objects_baseBuckets          resb 0x41a0; 0x3e1c  __GL_BUCKET_COUNT 
.texture_Defaults                     resb 0x1878; 0x7fbc  R		__GL_NUMBER_OF_TEXTURE_TARGETS] 
.texture_Active                       resd 0x004; 0x9834  R		Number of texture units 
.padding_9844                          resb 0x00c 
.viewport_ScaleX                      resd 0x004; 0x9850  R		Scale factor applied after perspective divide.  All four contain same data on PIII otherwize only [0] is valid 
.viewport_ScaleY                      resd 0x004; 0x9860  R		Scale factor applied after perspective divide.  All four contain same data on PIII otherwize only [0] is valid 
.viewport_ScaleZ                      resd 0x004; 0x9870  R		Scale factor applied after perspective divide.  All four contain same data on PIII otherwize only [0] is valid 
.viewport_CenterX                     resd 0x004; 0x9880  R		Offset factor applied after perspective divide.  All four contain same data on PIII otherwize only [0] is valid 
.viewport_CenterY                     resd 0x004; 0x9890  R		Offset factor applied after perspective divide.  All four contain same data on PIII otherwize only [0] is valid 
.viewport_CenterZ                     resd 0x004; 0x98a0  R		Offset factor applied after perspective divide.  All four contain same data on PIII otherwize only [0] is valid 
.viewport_BoundsX1                    resd 0x001; 0x98b0  R		Screenspace lower X bound, inclusive 
.viewport_BoundsX2                    resd 0x001; 0x98b4  R		Screenspace upper X bound, exclusive 
.viewport_BoundsY1                    resd 0x001; 0x98b8  R		Screenspace lower Y bound, inclusive 
.viewport_BoundsY2                    resd 0x001; 0x98bc  R		Screenspace upper Y bound, exclusive 
.procs_triangleFillFront              resd 0x001; 0x98c0
.procs_triangleFillFrontOdd3          resd 0x001; 0x98c4
.procs_triangleFillFrontOdd1          resd 0x001; 0x98c8
.procs_triangleFillFrontEven3         resd 0x001; 0x98cc
.procs_triangleFillFrontEven1         resd 0x001; 0x98d0
.procs_triangleFillFrontFan3          resd 0x001; 0x98d4
.procs_triangleFillFrontFan1          resd 0x001; 0x98d8
.procs_triangleFillFrontUnordered       resd 0x001; 0x98dc
.procs_triangleFillBack               resd 0x001; 0x98e0
.procs_triangleFillBackOdd3           resd 0x001; 0x98e4
.procs_triangleFillBackOdd1           resd 0x001; 0x98e8
.procs_triangleFillBackEven3          resd 0x001; 0x98ec
.procs_triangleFillBackEven1          resd 0x001; 0x98f0
.procs_triangleFillBackFan3           resd 0x001; 0x98f4
.procs_triangleFillBackFan1           resd 0x001; 0x98f8
.procs_triangleFillBackUnordered       resd 0x001; 0x98fc
.procs_triangleLineFront              resd 0x001; 0x9900
.procs_triangleLineFrontOdd3          resd 0x001; 0x9904
.procs_triangleLineFrontOdd1          resd 0x001; 0x9908
.procs_triangleLineFrontEven3         resd 0x001; 0x990c
.procs_triangleLineFrontEven1         resd 0x001; 0x9910
.procs_triangleLineFrontFan3          resd 0x001; 0x9914
.procs_triangleLineFrontFan1          resd 0x001; 0x9918
.procs_triangleLineFrontUnordered       resd 0x001; 0x991c
.procs_triangleLineBack               resd 0x001; 0x9920
.procs_triangleLineBackOdd3           resd 0x001; 0x9924
.procs_triangleLineBackOdd1           resd 0x001; 0x9928
.procs_triangleLineBackEven3          resd 0x001; 0x992c
.procs_triangleLineBackEven1          resd 0x001; 0x9930
.procs_triangleLineBackFan3           resd 0x001; 0x9934
.procs_triangleLineBackFan1           resd 0x001; 0x9938
.procs_triangleLineBackUnordered       resd 0x001; 0x993c
.procs_trianglePointFront             resd 0x001; 0x9940
.procs_trianglePointFrontOdd3         resd 0x001; 0x9944
.procs_trianglePointFrontOdd1         resd 0x001; 0x9948
.procs_trianglePointFrontEven3        resd 0x001; 0x994c
.procs_trianglePointFrontEven1        resd 0x001; 0x9950
.procs_trianglePointFrontFan3         resd 0x001; 0x9954
.procs_trianglePointFrontFan1         resd 0x001; 0x9958
.procs_trianglePointFrontUnordered       resd 0x001; 0x995c
.procs_trianglePointBack              resd 0x001; 0x9960
.procs_trianglePointBackOdd3          resd 0x001; 0x9964
.procs_trianglePointBackOdd1          resd 0x001; 0x9968
.procs_trianglePointBackEven3         resd 0x001; 0x996c
.procs_trianglePointBackEven1         resd 0x001; 0x9970
.procs_trianglePointBackFan3          resd 0x001; 0x9974
.procs_trianglePointBackFan1          resd 0x001; 0x9978
.procs_trianglePointBackUnordered       resd 0x001; 0x997c
.procs_line                           resd 0x001; 0x9980
.procs_lineLoop                       resd 0x001; 0x9984
.procs_lineUnordered                  resd 0x001; 0x9988
.procs_point                          resd 0x001; 0x998c
.procs_pointUnordered                 resd 0x001; 0x9990
.procs_depthTestEnable                resd 0x001; 0x9994
.procs_depthClear                     resd 0x001; 0x9998
.procs_depthFunc                      resd 0x001; 0x999c
.procs_depthMask                      resd 0x001; 0x99a0
.procs_setDepthState                  resd 0x001; 0x99a4
.procs_fogEnable                      resd 0x001; 0x99a8
.procs_fogColor                       resd 0x001; 0x99ac
.procs_setFogState                    resd 0x001; 0x99b0
.procs_alphaTestEnable                resd 0x001; 0x99b4
.procs_alphaFunc                      resd 0x001; 0x99b8
.procs_blendEnable                    resd 0x001; 0x99bc
.procs_blendFunc                      resd 0x001; 0x99c0
.procs_colorClear                     resd 0x001; 0x99c4
.procs_colorMask                      resd 0x001; 0x99c8
.procs_colorDrawBuffer                resd 0x001; 0x99cc
.procs_setColorState                  resd 0x001; 0x99d0
.procs_polyStippleEnable              resd 0x001; 0x99d4
.procs_polyStippleMask                resd 0x001; 0x99d8
.procs_setPolyStippleState            resd 0x001; 0x99dc
.procs_scissorTestEnable              resd 0x001; 0x99e0
.procs_scissorRect                    resd 0x001; 0x99e4
.procs_setScissorState                resd 0x001; 0x99e8
.procs_stencilTestEnable              resd 0x001; 0x99ec
.procs_stencilMask                    resd 0x001; 0x99f0
.procs_stencilFunc                    resd 0x001; 0x99f4
.procs_stencilOp                      resd 0x001; 0x99f8
.procs_stencilClear                   resd 0x001; 0x99fc
.procs_setStencilState                resd 0x001; 0x9a00
.procs_textureEnable                  resd 0x001; 0x9a04
.procs_textureSWrapMode               resd 0x001; 0x9a08
.procs_textureTWrapMode               resd 0x001; 0x9a0c
.procs_textureMinFilter               resd 0x001; 0x9a10
.procs_textureMagFilter               resd 0x001; 0x9a14
.procs_textureBorderColor             resd 0x001; 0x9a18
.procs_textureEnvMode                 resd 0x001; 0x9a1c
.procs_textureEnvColor                resd 0x001; 0x9a20
.procs_setTextureState                resd 0x001; 0x9a24
.procs_textureSelect                  resd 0x001; 0x9a28
.procs_textureDelete                  resd 0x001; 0x9a2c
.procs_textureProxyGetType1D          resd 0x001; 0x9a30
.procs_textureProxyGetType2D          resd 0x001; 0x9a34
.procs_textureProxyGetType3D          resd 0x001; 0x9a38
.procs_textureGetType1D               resd 0x001; 0x9a3c
.procs_textureGetType2D               resd 0x001; 0x9a40
.procs_textureGetType3D               resd 0x001; 0x9a44
.procs_textureImage1D                 resd 0x001; 0x9a48
.procs_textureImage2D                 resd 0x001; 0x9a4c
.procs_textureImage3D                 resd 0x001; 0x9a50
.procs_textureSubImage1D              resd 0x001; 0x9a54
.procs_textureSubImage2D              resd 0x001; 0x9a58
.procs_textureSubImage3D              resd 0x001; 0x9a5c
.procs_textureExtractPixel1D          resd 0x001; 0x9a60
.procs_textureExtractPixel2D          resd 0x001; 0x9a64
.procs_textureExtractPixel3D          resd 0x001; 0x9a68
.procs_textureIsResident              resd 0x001; 0x9a6c
.procs_shutdown                       resd 0x001; 0x9a70
.procs_viewportCreate                 resd 0x001; 0x9a74
.procs_viewportDestroy                resd 0x001; 0x9a78
.procs_bufferClear                    resd 0x001; 0x9a7c
.procs_bufferSwap                     resd 0x001; 0x9a80
.procs_bufferLock                     resd 0x001; 0x9a84
.procs_bufferUnlock                   resd 0x001; 0x9a88
.procs_bufferLoadScanline             resd 0x001; 0x9a8c
.procs_bufferStoreScanline            resd 0x001; 0x9a90
.procs_bufferVerifyMode               resd 0x001; 0x9a94
.procs_flush                          resd 0x001; 0x9a98
.procs_finish                         resd 0x001; 0x9a9c
.procs_polySmoothEnabled              resd 0x001; 0x9aa0
.procs_polyOffset                     resd 0x001; 0x9aa4
.procs_polyOffsetFillEnable           resd 0x001; 0x9aa8
.procs_polyOffsetLineEnable           resd 0x001; 0x9aac
.procs_polyOffsetPointEnable          resd 0x001; 0x9ab0
.procs_SetPolyState                   resd 0x001; 0x9ab4
.procs_SetLineWidth                   resd 0x001; 0x9ab8
.procs_SetPointSize                   resd 0x001; 0x9abc
.procs_resetRasterProcs               resd 0x001; 0x9ac0
.procs_setShadeMode                   resd 0x001; 0x9ac4
.procs_roundZValue                    resd 0x001; 0x9ac8
.procs_abort                          resd 0x001; 0x9acc  Called to abort any rendering in progress.  Engine should be idle before returning. 
.procs_lockClipList                   resd 0x001; 0x9ad0
.procs_unlockClipList                 resd 0x001; 0x9ad4
.procs_processThreadEvent             resd 0x001; 0x9ad8  Called as a result of releasing the thread sem.  Can potentially be called more often. 
.procs_callback_StoreFrontScanline       resd 0x001; 0x9adc  R	Callback for storing the front scanline if the driver cannot copy the front buffer to the frame buffer for some reason. 
.procs_callback_ProcChange            resd 0x001; 0x9ae0  R		Callback for the driver to notify GL that one or more of the drawing procs  
.procs_callback_GetOffsetBias         resd 0x001; 0x9ae4  R Callback to calculate the offset for a triangle.  Figured for 32bit float Z buffer using range 0 to 1 
.procs_callback_Perform               resd 0x001; 0x9ae8  R Callback to cause libGL2 to perform one or more tasks.  See the defines. 
.primitive_Count                      resd 0x001; 0x9aec  Records the next primitive vertex to be processed. 
.primitive_GroupProcessor             resd 0x001; 0x9af0  Processor for the beginning or middle of primitive processing. 
.primitive_End                        resd 0x001; 0x9af4  Processor for the end of primitive groups that can handle partial SIMD groups. 
.primitive_CacheCurrentNeeds          resd 0x001; 0x9af8  The current needs for primitive processing. 
.primitive_CacheProcess               resd 0x00a; 0x9afc  The current GroupProcessors for the various primitives. NULL means they need to be looked up or generated. 
.primitive_CacheEnd                   resd 0x00a; 0x9b24  The current Ends for the various primitives. NULL means they need to be looked up or generated. 
.primitive_CacheCode                  resd 0x020; 0x9b4c  PRIM_CACHE_SIZE, Needs code for cache entry 
.primitive_CacheAge                   resd 0x020; 0x9bcc  PRIM_CACHE_SIZE, Age of cache entry 
.primitive_CacheProcessPtrs           resd 0x020; 0x9c4c  PRIM_CACHE_SIZE, Pointer to processing routine past SIMD prefix. 
.primitive_CacheAllocation            resd 0x001; 0x9ccc  Pointer to the allocation of memory for the cache. 
.primitive_ClippedPolyProcFront       resd 0x001; 0x9cd0  The current unordered triangle proc for front facing triangles. 
.primitive_ClippedPolyProcBack        resd 0x001; 0x9cd4  The current unordered triangle proc for back facing triangles. 
.primitive_EdgeTag                    resd 0x001; 0x9cd8  The current edge tag.  1=Draw edge,  0=Do not draw edge 
.primitive_CullAndMask                resb 0x001; 0x9cdc  0x00 = disabled,  0xff=enabled 
.primitive_CullXorMask                resb 0x001; 0x9cdd  0x01 = GL_BACK, 0x00=GL_FRONT, 0x10=GL_FRONT_AND_BACK 
.primitive_CullCurrentFacing          resb 0x001; 0x9cde
.primitive_FacingXorMask              resb 0x001; 0x9cdf  0x00 = GL_CCW,  0x01=GL_CW 
.primitive_Provoking                  resd 0x001; 0x9ce0  The provoking vertex for flat shading.  Use to select color. 
.primitive_CallSize                   resd 0x001; 0x9ce4  The current call point for SIMD vertex processors. 
.primitive_FirstVertexInGroup         resd 0x001; 0x9ce8
.primitive_CurrentGroupCount          resd 0x001; 0x9cec
.primitive_CurrentVertex              resd 0x001; 0x9cf0  The vertex that the next call to glVertexNXX will use. 
.primitive_StripFlag                  resd 0x001; 0x9cf4
.primitive_ColorScale_R               resd 0x001; 0x9cf8
.primitive_ColorScale_G               resd 0x001; 0x9cfc
.primitive_ColorScale_B               resd 0x001; 0x9d00
.primitive_ColorScale_A               resd 0x001; 0x9d04
.clipInfo                             resd 0x001; 0x9d08  
.software_ProcsCurrent                resb 0x001; 0x9d0c
.software_PathColorEnable             resb 0x001; 0x9d0d
.software_PathDisable                 resb 0x001; 0x9d0e
.padding_9d0f                          resb 0x001 
.buffer_ScanlineFB                    resd 0x001; 0x9d10  NA	Scanline buffer, holds a color scanline to be written to the HW buffer.  
.buffer_ScanlineFBIN                  resd 0x001; 0x9d14  NA	Scanline buffer, holds a color scanline read from the HW buffer.  
.buffer_ScanlineA                     resd 0x001; 0x9d18  NA	Scanline buffer, holds a accumulation buffer scanline read from or to be written to HW. 
.buffer_ScanlineZ                     resd 0x001; 0x9d1c  NA	Scanline buffer, holds a depth buffer scanline read from or to be written to HW 
.buffer_ScanlineS                     resd 0x001; 0x9d20  NA	Scanline buffer, holds a stencil buffer scanline read from or to be written to HW. 
.buffer_ScanlineV                     resd 0x001; 0x9d24  NA	Scanline Valid buffer, contains 1s for pixels to be written and 0s for not. 
.buffer_ScanlineY                     resd 0x001; 0x9d28  R		Scanline buffer, The Y coordinate for the current scanline. 
.buffer_Height                        resd 0x001; 0x9d2c  R		Height of the front buffer in pixels 
.buffer_Width                         resd 0x001; 0x9d30  R		Width of the front buffer in pixels 
.buffer_ColorFront                    resd 0x001; 0x9d34  R		Pointer to the softawre front color buffer if pressent. 
.buffer_ColorBack                     resd 0x001; 0x9d38  R		Pointer to the softawre back color buffer if pressent. 
.buffer_Depth                         resd 0x001; 0x9d3c  R		Pointer to the softawre depth buffer if pressent. 
.buffer_Accum                         resd 0x001; 0x9d40  R		Pointer to the softawre accumulation buffer if pressent. 
.buffer_Stencil                       resd 0x001; 0x9d44  R		Pointer to the softawre stencil buffer if pressent. 
.buffer_FullScreen                    resd 0x001; 0x9d48  R		Flag to indicate if the application has exclusive access to the screen. 
.buffer_ColorFrontHardware            resd 0x001; 0x9d4c  RW	Front buffer	1=HW  0=Fallback 
.buffer_ColorBackEnabled              resd 0x001; 0x9d50  R 
.buffer_ColorBackHardware             resd 0x001; 0x9d54  RW	Back buffer	1=HW  0=Fallback 
.buffer_DepthEnabled                  resd 0x001; 0x9d58  R 
.buffer_DepthHardware                 resd 0x001; 0x9d5c  RW	1=HW  0=Fallback 
.buffer_AccumEnabled                  resd 0x001; 0x9d60  R 
.buffer_AccumHardware                 resd 0x001; 0x9d64  RW	1=HW  0=Fallback 
.buffer_StencilEnabled                resd 0x001; 0x9d68  R		Flag to indicate if the user specified a stencil buffer be created. 
.buffer_StencilHardware               resd 0x001; 0x9d6c  RW	1=HW  0=Fallback 
.buffer_ColorScale_R                  resd 0x001; 0x9d70
.buffer_ColorScale_G                  resd 0x001; 0x9d74
.buffer_ColorScale_B                  resd 0x001; 0x9d78
.buffer_ColorScale_A                  resd 0x001; 0x9d7c
.buffer_bitsRed                       resd 0x001; 0x9d80  RW	Set the bit count in AcceleratorInit 
.buffer_bitsGreen                     resd 0x001; 0x9d84  RW	Set the bit count in AcceleratorInit 
.buffer_bitsBlue                      resd 0x001; 0x9d88  RW	Set the bit count in AcceleratorInit 
.buffer_bitsAlpha                     resd 0x001; 0x9d8c  RW	Set the bit count in AcceleratorInit 
.buffer_bitsDepth                     resd 0x001; 0x9d90  RW	Set the bit count in AcceleratorInit 
.buffer_bitsStencil                   resd 0x001; 0x9d94  RW	Set the bit count in AcceleratorInit 
.buffer_bitsAccumRed                  resd 0x001; 0x9d98  RW	Set the bit count in AcceleratorInit 
.buffer_bitsAccumGreen                resd 0x001; 0x9d9c  RW	Set the bit count in AcceleratorInit 
.buffer_bitsAccumBlue                 resd 0x001; 0x9da0  RW	Set the bit count in AcceleratorInit 
.buffer_bitsAccumAlpha                resd 0x001; 0x9da4  RW	Set the bit count in AcceleratorInit 
.buffer_UserColor                     resd 0x001; 0x9da8  R 
.buffer_UserDepth                     resd 0x001; 0x9dac  R 
.buffer_UserStencil                   resd 0x001; 0x9db0  R 
.buffer_UserAccum                     resd 0x001; 0x9db4  R 
.buffer_RefreshRate                   resd 0x001; 0x9db8  R		Refresh rate for fullscreen mode 
.buffer_gammaRed                      resd 0x001; 0x9dbc  R 
.buffer_gammaGreen                    resd 0x001; 0x9dc0  R 
.buffer_gammaBlue                     resd 0x001; 0x9dc4  R 
.valid_All                            resd 0x001; 0x9dc8
.valid_ModelMatrix                    resd 0x001; 0x9dcc
.valid_ProjectionMatrix               resd 0x001; 0x9dd0
.valid_VertexProcs                    resd 0x001; 0x9dd4
.valid_LightData                      resd 0x001; 0x9dd8
.valid_PrimProcessor                  resd 0x001; 0x9ddc
.valid_VapiProcessor                  resd 0x001; 0x9de0
.valid_ModelMatrixType                resd 0x001; 0x9de4
.valid_ProjectionMatrixType           resd 0x001; 0x9de8
.valid_MVPMatrixType                  resd 0x001; 0x9dec  
.methods_ec1                          resd 0x001; 0x9df0
.methods_ec2                          resd 0x001; 0x9df4
.methods_matValidate                  resd 0x001; 0x9df8
.methods_bitmap                       resd 0x001; 0x9dfc
.methods_renderBitmap                 resd 0x001; 0x9e00
.methods_lineClipParam                resd 0x001; 0x9e04
.methods_readPixels                   resd 0x001; 0x9e08
.methods_fogPoint                     resd 0x001; 0x9e0c
.methods_error                        resd 0x001; 0x9e10
.attributes_stack                     resd 0x010; 0x9e14  __GL_ATTRIB_STACK_DEPTH 
.attributes_clientStack               resd 0x010; 0x9e54  __GL_CLIENT_ATTRIB_STACK_DEPTH 
.attributes_stackPointer              resd 0x001; 0x9e94
.attributes_clientStackPointer        resd 0x001; 0x9e98
.vertex_MaterialNeeds                 resd 0x001; 0x9e9c
.vertex_TransformGroupCurrent         resd 0x001; 0x9ea0
.vertex_TransformGroup                resd 0x002; 0x9ea4
.vertex_TransformerCacheAge           resd 0x010; 0x9eac  VAPI_CACHE_SIZE 
.vertex_TransformerCacheCode          resd 0x010; 0x9eec  VAPI_CACHE_SIZE 
.vertex_TransformerCacheGroup         resd 0x010; 0x9f2c  VAPI_CACHE_SIZE, Transform code. For glEnd. 
.vertex_VapiNeeds                     resd 0x001; 0x9f6c
.vertex_XformNeeds                    resd 0x001; 0x9f70
.vertex_CacheAllocation               resd 0x001; 0x9f74  
.transform_maxWindowDimension         resd 0x001; 0x9f78
.transform_modelViewStack             resb 0x1880; 0x9f7c  __GL_MODELVIEW_STACK_DEPTH 
.transform_modelView                  resd 0x001; 0xb7fc
.transform_projectionStack            resb 0x7a8; 0xb800  __GL_PROJECTION_STACK_DEPTH 
.transform_projection                 resd 0x001; 0xbfa8
.transform_projectionSequence         resd 0x001; 0xbfac
.transform_textureStack               resb 0x7a8; 0xbfb0  __GL_TEXTURE_STACK_DEPTH 
.transform_texture                    resd 0x001; 0xc758
.transform_matrixIsIdent              resb 0x001; 0xc75c
.padding_c75d                          resb 0x003 
.list_shared                          resd 0x001; 0xc760
.list_openList                        resd 0x001; 0xc764
.list_pc                              resd 0x001; 0xc768
.list_mode                            resd 0x001; 0xc76c
.list_nesting                         resd 0x001; 0xc770  
.evaluator_eval1                      resb 0x090; 0xc774  __GL_MAP_RANGE_COUNT 
.evaluator_eval2                      resb 0x0fc; 0xc804  __GL_MAP_RANGE_COUNT 
.evaluator_eval1Data                  resd 0x009; 0xc900  __GL_MAP_RANGE_COUNT 
.evaluator_eval2Data                  resd 0x009; 0xc924  __GL_MAP_RANGE_COUNT 
.feedback_overFlowed                  resb 0x001; 0xc948
.padding_c949                          resb 0x003 
.feedback_resultBase                  resd 0x001; 0xc94c
.feedback_result                      resd 0x001; 0xc950
.feedback_resultLength                resd 0x001; 0xc954
.feedback_type                        resd 0x001; 0xc958  
.line_stipplePosition                 resd 0x001; 0xc95c
.line_repeat                          resd 0x001; 0xc960
.select_hit                           resb 0x001; 0xc964
.padding_c965                          resb 0x003 
.select_stack                         resd 0x080; 0xc968  __GL_NAME_STACK_DEPTH 
.select_sp                            resd 0x001; 0xcb68
.select_overFlowed                    resb 0x001; 0xcb6c
.padding_cb6d                          resb 0x003 
.select_resultBase                    resd 0x001; 0xcb70
.select_result                        resd 0x001; 0xcb74
.select_resultLength                  resd 0x001; 0xcb78
.select_hits                          resd 0x001; 0xcb7c
.select_z                             resd 0x001; 0xcb80  
.padding_cb84                          resb 0x00c 
.light_source                         resb 0x980; 0xcb90  __GL_NUMBER_OF_LIGHTS 
.light_material                       resb 0x020; 0xd510
.light_sources                        resd 0x001; 0xd530
.light_List                           resd 0x008; 0xd534
.light_NumberActive                   resd 0x001; 0xd554
.light_UseSlow                        resd 0x001; 0xd558
.padding_d55c                          resb 0x004 
.vertexArray_vertexCall               resd 0x001; 0xd560
.vertexArray_normalCall               resd 0x001; 0xd564
.vertexArray_colorCall                resd 0x001; 0xd568
.vertexArray_indexCall                resd 0x001; 0xd56c
.vertexArray_texCoordCall             resd 0x001; 0xd570
.vertexArray_edgeFlagCall             resd 0x001; 0xd574
.vertexArray_vertexSkip               resd 0x001; 0xd578
.vertexArray_normalSkip               resd 0x001; 0xd57c
.vertexArray_colorSkip                resd 0x001; 0xd580
.vertexArray_indexSkip                resd 0x001; 0xd584
.vertexArray_texCoordSkip             resd 0x004; 0xd588
.vertexArray_edgeFlagSkip             resd 0x001; 0xd598  
.vertexArray_drawElementCodeCache       resd 0x008; 0xd59c  [4096 * 8] 
.vertexArray_drawElementNeeds         resd 0x008; 0xd5bc
.vertexArray_drawElementAge           resd 0x008; 0xd5dc
.vertexArray_drawElementCurrentNeeds       resd 0x001; 0xd5fc
.softScanProcs_scanlineDepth          resd 0x001; 0xd600
.softScanProcs_loadBits               resd 0x001; 0xd604
.softScanProcs_storeBits              resd 0x001; 0xd608
.softScanProcs_valid                  resb 0x001; 0xd60c
.softScanProcs_maskEnabled            resb 0x001; 0xd60d
.softScanProcs_colorWriteEnabled       resb 0x001; 0xd60e
.softScanProcs_fastScanline           resb 0x001; 0xd60f
.softScanProcs_processorFuncData       resd 0x001; 0xd610
.softScanProcs_processorFunc          resd 0x001; 0xd614
.softScanProcs_processorNeeds         resd 0x001; 0xd618  
.info_state_h_version                 resd 0x001; 0xd61c  R 
.info_textureMaxS                     resd 0x001; 0xd620  RW 
.info_textureMaxT                     resd 0x001; 0xd624  RW 
.info_textureMaxR                     resd 0x001; 0xd628  RW 
.info_vendor                          resd 0x001; 0xd62c  R  
.info_renderer                        resd 0x001; 0xd630  R 
.info_version                         resd 0x001; 0xd634  R 
.info_extensions                      resd 0x001; 0xd638  R 
.info_hwRenderer                      resd 0x001; 0xd63c  RW Defaults to null, set string to name of HW renderer if present 
.info_hwGeometry                      resd 0x001; 0xd640  RW Defaults to null, set string to name of HW geometry if present 
.info_comboStrings                    resd 0x003; 0xd644  R  The three strings that are possible for GL_RENDERER 
.info_debugLock                       resb 0x001; 0xd650  R 
.info_debugDevices                    resb 0x001; 0xd651  R 
.info_debugDriver                     resb 0x001; 0xd652  R 
.info_debugModes                      resb 0x001; 0xd653  R 
.info_debugOther                      resb 0x001; 0xd654  R 
.info_debugDisableDCLock              resb 0x001; 0xd655  R 
.padding_d656                          resb 0x002 
.window_UtilThreadSem                 resd 0x001; 0xd658  R sem_id that triggers the util thread.  Releasing it will trigger a call to processThreadEvent. 
.window_DirectWindow                  resd 0x001; 0xd65c  NA 
.immedTable_Color3bv                  resd 0x001; 0xd660
.immedTable_Color3dv                  resd 0x001; 0xd664
.immedTable_Color3fv                  resd 0x001; 0xd668
.immedTable_Color3iv                  resd 0x001; 0xd66c
.immedTable_Color3sv                  resd 0x001; 0xd670
.immedTable_Color3ubv                 resd 0x001; 0xd674
.immedTable_Color3uiv                 resd 0x001; 0xd678
.immedTable_Color3usv                 resd 0x001; 0xd67c
.immedTable_Color4bv                  resd 0x001; 0xd680
.immedTable_Color4dv                  resd 0x001; 0xd684
.immedTable_Color4fv                  resd 0x001; 0xd688
.immedTable_Color4iv                  resd 0x001; 0xd68c
.immedTable_Color4sv                  resd 0x001; 0xd690
.immedTable_Color4ubv                 resd 0x001; 0xd694
.immedTable_Color4uiv                 resd 0x001; 0xd698
.immedTable_Color4usv                 resd 0x001; 0xd69c
.immedTable_Normal3fv                 resd 0x001; 0xd6a0
.immedTable_TexCoord1fv               resd 0x001; 0xd6a4
.immedTable_TexCoord2fv               resd 0x001; 0xd6a8
.immedTable_TexCoord3fv               resd 0x001; 0xd6ac
.immedTable_TexCoord4fv               resd 0x001; 0xd6b0
.immedTable_Vertex2fv                 resd 0x001; 0xd6b4
.immedTable_Vertex3fv                 resd 0x001; 0xd6b8
.immedTable_Vertex4fv                 resd 0x001; 0xd6bc
.immedTable_Begin                     resd 0x001; 0xd6c0
.immedTable_End                       resd 0x001; 0xd6c4
.immedTable_CallList                  resd 0x001; 0xd6c8
.immedTable_CallLists                 resd 0x001; 0xd6cc
.immedTable_ListBase                  resd 0x001; 0xd6d0
.immedTable_Bitmap                    resd 0x001; 0xd6d4
.immedTable_EdgeFlag                  resd 0x001; 0xd6d8
.immedTable_EdgeFlagv                 resd 0x001; 0xd6dc
.immedTable_Indexd                    resd 0x001; 0xd6e0
.immedTable_Indexdv                   resd 0x001; 0xd6e4
.immedTable_Indexf                    resd 0x001; 0xd6e8
.immedTable_Indexfv                   resd 0x001; 0xd6ec
.immedTable_Indexi                    resd 0x001; 0xd6f0
.immedTable_Indexiv                   resd 0x001; 0xd6f4
.immedTable_Indexs                    resd 0x001; 0xd6f8
.immedTable_Indexsv                   resd 0x001; 0xd6fc
.immedTable_Indexub                   resd 0x001; 0xd700
.immedTable_Indexubv                  resd 0x001; 0xd704
.immedTable_RasterPos2d               resd 0x001; 0xd708
.immedTable_RasterPos2dv              resd 0x001; 0xd70c
.immedTable_RasterPos2f               resd 0x001; 0xd710
.immedTable_RasterPos2fv              resd 0x001; 0xd714
.immedTable_RasterPos2i               resd 0x001; 0xd718
.immedTable_RasterPos2iv              resd 0x001; 0xd71c
.immedTable_RasterPos2s               resd 0x001; 0xd720
.immedTable_RasterPos2sv              resd 0x001; 0xd724
.immedTable_RasterPos3d               resd 0x001; 0xd728
.immedTable_RasterPos3dv              resd 0x001; 0xd72c
.immedTable_RasterPos3f               resd 0x001; 0xd730
.immedTable_RasterPos3fv              resd 0x001; 0xd734
.immedTable_RasterPos3i               resd 0x001; 0xd738
.immedTable_RasterPos3iv              resd 0x001; 0xd73c
.immedTable_RasterPos3s               resd 0x001; 0xd740
.immedTable_RasterPos3sv              resd 0x001; 0xd744
.immedTable_RasterPos4d               resd 0x001; 0xd748
.immedTable_RasterPos4dv              resd 0x001; 0xd74c
.immedTable_RasterPos4f               resd 0x001; 0xd750
.immedTable_RasterPos4fv              resd 0x001; 0xd754
.immedTable_RasterPos4i               resd 0x001; 0xd758
.immedTable_RasterPos4iv              resd 0x001; 0xd75c
.immedTable_RasterPos4s               resd 0x001; 0xd760
.immedTable_RasterPos4sv              resd 0x001; 0xd764
.immedTable_Rectd                     resd 0x001; 0xd768
.immedTable_Rectdv                    resd 0x001; 0xd76c
.immedTable_Rectf                     resd 0x001; 0xd770
.immedTable_Rectfv                    resd 0x001; 0xd774
.immedTable_Recti                     resd 0x001; 0xd778
.immedTable_Rectiv                    resd 0x001; 0xd77c
.immedTable_Rects                     resd 0x001; 0xd780
.immedTable_Rectsv                    resd 0x001; 0xd784
.immedTable_ClipPlane                 resd 0x001; 0xd788
.immedTable_ColorMaterial             resd 0x001; 0xd78c
.immedTable_CullFace                  resd 0x001; 0xd790
.immedTable_Fogf                      resd 0x001; 0xd794
.immedTable_Fogfv                     resd 0x001; 0xd798
.immedTable_Fogi                      resd 0x001; 0xd79c
.immedTable_Fogiv                     resd 0x001; 0xd7a0
.immedTable_FrontFace                 resd 0x001; 0xd7a4
.immedTable_Hint                      resd 0x001; 0xd7a8
.immedTable_Lightf                    resd 0x001; 0xd7ac
.immedTable_Lightfv                   resd 0x001; 0xd7b0
.immedTable_Lighti                    resd 0x001; 0xd7b4
.immedTable_Lightiv                   resd 0x001; 0xd7b8
.immedTable_LightModelf               resd 0x001; 0xd7bc
.immedTable_LightModelfv              resd 0x001; 0xd7c0
.immedTable_LightModeli               resd 0x001; 0xd7c4
.immedTable_LightModeliv              resd 0x001; 0xd7c8
.immedTable_LineStipple               resd 0x001; 0xd7cc
.immedTable_LineWidth                 resd 0x001; 0xd7d0
.immedTable_Materialf                 resd 0x001; 0xd7d4
.immedTable_Materialfv                resd 0x001; 0xd7d8
.immedTable_Materiali                 resd 0x001; 0xd7dc
.immedTable_Materialiv                resd 0x001; 0xd7e0
.immedTable_PointSize                 resd 0x001; 0xd7e4
.immedTable_PolygonMode               resd 0x001; 0xd7e8
.immedTable_PolygonStipple            resd 0x001; 0xd7ec
.immedTable_Scissor                   resd 0x001; 0xd7f0
.immedTable_ShadeModel                resd 0x001; 0xd7f4
.immedTable_TexParameterf             resd 0x001; 0xd7f8
.immedTable_TexParameterfv            resd 0x001; 0xd7fc
.immedTable_TexParameteri             resd 0x001; 0xd800
.immedTable_TexParameteriv            resd 0x001; 0xd804
.immedTable_TexImage1D                resd 0x001; 0xd808
.immedTable_TexImage2D                resd 0x001; 0xd80c
.immedTable_TexEnvf                   resd 0x001; 0xd810
.immedTable_TexEnvfv                  resd 0x001; 0xd814
.immedTable_TexEnvi                   resd 0x001; 0xd818
.immedTable_TexEnviv                  resd 0x001; 0xd81c
.immedTable_TexGend                   resd 0x001; 0xd820
.immedTable_TexGendv                  resd 0x001; 0xd824
.immedTable_TexGenf                   resd 0x001; 0xd828
.immedTable_TexGenfv                  resd 0x001; 0xd82c
.immedTable_TexGeni                   resd 0x001; 0xd830
.immedTable_TexGeniv                  resd 0x001; 0xd834
.immedTable_InitNames                 resd 0x001; 0xd838
.immedTable_LoadName                  resd 0x001; 0xd83c
.immedTable_PassThrough               resd 0x001; 0xd840
.immedTable_PopName                   resd 0x001; 0xd844
.immedTable_PushName                  resd 0x001; 0xd848
.immedTable_DrawBuffer                resd 0x001; 0xd84c
.immedTable_Clear                     resd 0x001; 0xd850
.immedTable_ClearAccum                resd 0x001; 0xd854
.immedTable_ClearIndex                resd 0x001; 0xd858
.immedTable_ClearColor                resd 0x001; 0xd85c
.immedTable_ClearStencil              resd 0x001; 0xd860
.immedTable_ClearDepth                resd 0x001; 0xd864
.immedTable_StencilMask               resd 0x001; 0xd868
.immedTable_ColorMask                 resd 0x001; 0xd86c
.immedTable_DepthMask                 resd 0x001; 0xd870
.immedTable_IndexMask                 resd 0x001; 0xd874
.immedTable_Accum                     resd 0x001; 0xd878
.immedTable_Disable                   resd 0x001; 0xd87c
.immedTable_Enable                    resd 0x001; 0xd880
.immedTable_PopAttrib                 resd 0x001; 0xd884
.immedTable_PushAttrib                resd 0x001; 0xd888
.immedTable_Map1d                     resd 0x001; 0xd88c
.immedTable_Map1f                     resd 0x001; 0xd890
.immedTable_Map2d                     resd 0x001; 0xd894
.immedTable_Map2f                     resd 0x001; 0xd898
.immedTable_MapGrid1d                 resd 0x001; 0xd89c
.immedTable_MapGrid1f                 resd 0x001; 0xd8a0
.immedTable_MapGrid2d                 resd 0x001; 0xd8a4
.immedTable_MapGrid2f                 resd 0x001; 0xd8a8
.immedTable_EvalCoord1d               resd 0x001; 0xd8ac
.immedTable_EvalCoord1dv              resd 0x001; 0xd8b0
.immedTable_EvalCoord1f               resd 0x001; 0xd8b4
.immedTable_EvalCoord1fv              resd 0x001; 0xd8b8
.immedTable_EvalCoord2d               resd 0x001; 0xd8bc
.immedTable_EvalCoord2dv              resd 0x001; 0xd8c0
.immedTable_EvalCoord2f               resd 0x001; 0xd8c4
.immedTable_EvalCoord2fv              resd 0x001; 0xd8c8
.immedTable_EvalMesh1                 resd 0x001; 0xd8cc
.immedTable_EvalPoint1                resd 0x001; 0xd8d0
.immedTable_EvalMesh2                 resd 0x001; 0xd8d4
.immedTable_EvalPoint2                resd 0x001; 0xd8d8
.immedTable_AlphaFunc                 resd 0x001; 0xd8dc
.immedTable_BlendFunc                 resd 0x001; 0xd8e0
.immedTable_LogicOp                   resd 0x001; 0xd8e4
.immedTable_StencilFunc               resd 0x001; 0xd8e8
.immedTable_StencilOp                 resd 0x001; 0xd8ec
.immedTable_DepthFunc                 resd 0x001; 0xd8f0
.immedTable_PixelZoom                 resd 0x001; 0xd8f4
.immedTable_PixelTransferf            resd 0x001; 0xd8f8
.immedTable_PixelTransferi            resd 0x001; 0xd8fc
.immedTable_PixelMapfv                resd 0x001; 0xd900
.immedTable_PixelMapuiv               resd 0x001; 0xd904
.immedTable_PixelMapusv               resd 0x001; 0xd908
.immedTable_ReadBuffer                resd 0x001; 0xd90c
.immedTable_CopyPixels                resd 0x001; 0xd910
.immedTable_DrawPixels                resd 0x001; 0xd914
.immedTable_DepthRange                resd 0x001; 0xd918
.immedTable_Frustum                   resd 0x001; 0xd91c
.immedTable_LoadIdentity              resd 0x001; 0xd920
.immedTable_LoadMatrixf               resd 0x001; 0xd924
.immedTable_LoadMatrixd               resd 0x001; 0xd928
.immedTable_MatrixMode                resd 0x001; 0xd92c
.immedTable_MultMatrixf               resd 0x001; 0xd930
.immedTable_MultMatrixd               resd 0x001; 0xd934
.immedTable_Ortho                     resd 0x001; 0xd938
.immedTable_PopMatrix                 resd 0x001; 0xd93c
.immedTable_PushMatrix                resd 0x001; 0xd940
.immedTable_Rotated                   resd 0x001; 0xd944
.immedTable_Rotatef                   resd 0x001; 0xd948
.immedTable_Scaled                    resd 0x001; 0xd94c
.immedTable_Scalef                    resd 0x001; 0xd950
.immedTable_Translated                resd 0x001; 0xd954
.immedTable_Translatef                resd 0x001; 0xd958
.immedTable_Viewport                  resd 0x001; 0xd95c
.immedTable_PolygonOffset             resd 0x001; 0xd960
.immedTable_ArrayElement              resd 0x001; 0xd964
.immedTable_DrawArrays                resd 0x001; 0xd968
.immedTable_DrawElements              resd 0x001; 0xd96c
.immedTable_TexSubImage1D             resd 0x001; 0xd970
.immedTable_TexSubImage2D             resd 0x001; 0xd974
.immedTable_CopyTexImage1D            resd 0x001; 0xd978
.immedTable_CopyTexImage2D            resd 0x001; 0xd97c
.immedTable_CopyTexSubImage1D         resd 0x001; 0xd980
.immedTable_CopyTexSubImage2D         resd 0x001; 0xd984
.immedTable_BindTexture               resd 0x001; 0xd988
.immedTable_PrioritizeTextures        resd 0x001; 0xd98c
.immedTable_MultiTexCoord1fvARB       resd 0x001; 0xd990
.immedTable_MultiTexCoord2fvARB       resd 0x001; 0xd994
.immedTable_MultiTexCoord3fvARB       resd 0x001; 0xd998
.immedTable_MultiTexCoord4fvARB       resd 0x001; 0xd99c
.immedTable_ActiveTextureARB          resd 0x001; 0xd9a0
.flingerContext                       resd 0x001; 0xd9a4
.flingerCurrent                       resd 0x001; 0xd9a8
.flingerLOD                           resd 0x001; 0xd9ac
.usrVp1                               resd 0x001; 0xd9b0
.usrVp2                               resd 0x001; 0xd9b4
.usrVp3                               resd 0x001; 0xd9b8
.usrVp4                               resd 0x001; 0xd9bc
ENDSTRUC 

%endif 
