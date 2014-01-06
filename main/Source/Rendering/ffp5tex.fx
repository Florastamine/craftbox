///////////////////////////////////
//  ffp5tex.fx
//
/***********************************************************
   FFP MultiTex Effect to blend 5 Textures.

   5/8/05

   Eric Hendrickson-Lambert (Steempipe)


   Requires:  GStudio 6.31 Comm+
	      DX 9.0c

   Blendmaps for skins 2,3,4,5 are in their alpha channels

************************************************************/

////////////////////////////////////////////////////
// Assign the tile size of the Textures.
//

float Skin_Size1 = 20;
float Skin_Size2 = 20;
float Skin_Size3 = 20;
float Skin_Size4 = 20;
float Skin_Size5 = 20;


float4 vecLight;


/////////////////////////////////////////////////////////////////////////////////////
// Let's allow for adjusting the intensity of the ambient light color on the passes.
//
float ambientLightFactor = 1.0;


////////////////////////////////////////////////////////////////////
// Here we just create and plug some values into a matrix for
// use in multiplying during the stages.
//

float4x4 matTerrainTexSize =    {1.0, 0.0, 0.0 ,0.0,   
		    		 0.0, 1.0, 0.0, 0.0,   
		   		 0.0, 0.0, 0.0, 0.0,
		    		 0.0, 0.0, 0.0, 0.0
				};


float4x4 matAlphaMapSize = 	{1.0, 0.0, 0.0 ,0.0,
		    		 0.0, 1.0, 0.0, 0.0,
		    		 0.0, 0.0, 0.0, 0.0,
		    		 0.0, 0.0, 0.0, 0.0
				};


Texture entSkin1; 	//1st tile tex RGB
Texture mtlSkin1;	//2nd tile tex RGB and blender in A
Texture mtlSkin2;	//3nd tile tex RGB and blender in A
Texture mtlSkin3;	//4nd tile tex RGB and blender in A
Texture mtlSkin4;	//5nd tile tex RGB and blender in A


sampler s_ShaleTex = sampler_state
{
    Texture = (entSkin1);
    MipFilter = Linear;
    MinFilter = Linear;
    MagFilter = Linear;
    AddressU  = Wrap;
    AddressV  = Wrap;
    AddressW  = Wrap;
    MaxMipLevel=0;
    MipMapLodBias=0.0;
};


sampler s_SandTex = sampler_state
{
    Texture = (mtlSkin1);
    MipFilter = Linear;
    MinFilter = Linear;
    MagFilter = Linear;
    AddressU  = Wrap;
    AddressV  = Wrap;
    AddressW  = Wrap;
    MaxMipLevel=0;
    MipMapLodBias=0.0;
};


sampler s_GrassTex = sampler_state
{
    Texture = (mtlSkin2);
    MipFilter = Linear;
    MinFilter = Linear;
    MagFilter = Linear;
    AddressU  = Wrap;
    AddressV  = Wrap;
    AddressW  = Wrap;
    MaxMipLevel=0;
    MipMapLodBias=0.0;
};


sampler s_RoadTex = sampler_state
{
    Texture = (mtlSkin3);
    MipFilter = Linear;
    MinFilter = Linear;
    MagFilter = Linear;
    AddressU  = Wrap;
    AddressV  = Wrap;
    AddressW  = Wrap;
    MaxMipLevel=0;
    MipMapLodBias=0.0;
};

sampler s_StoneTex = sampler_state
{
    Texture = (mtlSkin4);
    MipFilter = Linear;
    MinFilter = Linear;
    MagFilter = Linear;
    AddressU  = Wrap;
    AddressV  = Wrap;
    AddressW  = Wrap;
    MaxMipLevel=0;
    MipMapLodBias=0.0;
};


	
technique technique_one

  {
   	
    pass p0
      {
	Sampler[0]	= (s_ShaleTex);
	
	AlphaBlendEnable = False;
	AlphaTestEnable = False;
	DitherEnable = True;
	zWriteEnable = True;
      	zEnable = True;
	CullMode = None;
	Lighting=True;		
	
	Ambient = mul(vecLight, ambientLightFactor);
	
	TextureTransformFlags[0] = Count2;
	TexCoordIndex[0] = 1;
	TextureTransform[0]= mul(matTerrainTexSize,Skin_Size1);
						
	ColorOp[0] = Modulate;	
	ColorArg1[0] = Texture;
	ColorArg2[0] = Diffuse;
	AlphaOp[0] = Disable;
	
     
      }


    pass p1 
      {
	Sampler[0] 	= (s_SandTex);   	// Blendmap is Alpha
	Sampler[1] 	= (s_SandTex);     	// The Colormap 
	
	Lighting = True;
	Clipping=True;
	DitherEnable=True;
	         		
	AlphaBlendEnable = True;
	AlphaTestEnable = False;
	SrcBlend = InvSrcAlpha;
	DestBlend = SrcAlpha;

	DitherEnable = True;
	zWriteEnable = True;
      	zEnable = True;
	CullMode = None;
	Lighting=True;		
	
	Ambient = mul(vecLight, ambientLightFactor);

	TextureTransformFlags[0] = Count2;		
	TextureTransform[0]= (matAlphaMapSize);
	texcoordindex[0]=0;
	ColorArg1[0] = Texture; 
        ColorOp[0] = SelectArg1;
        AlphaArg1[0] = Texture;
        AlphaOp[0] = SelectArg1;

	TextureTransformFlags[1] = Count2;		
	TextureTransform[1]= mul(matTerrainTexSize, Skin_Size2);
	texcoordindex[1]=1;

	ColorArg1[1] = Texture; 
	ColorArg2[1]= Diffuse;
        ColorOp[1] =Modulate;
        alphaarg1[1] = current;
        alphaop[1]=Disable;

      }

    pass p2
      {
	Sampler[0] 	= (s_GrassTex);   	// Blendmap is Alpha
	Sampler[1] 	= (s_GrassTex);     	// The Colormap 
		
	Lighting = True;
	Clipping=True;
	DitherEnable=True;
		
	AlphaBlendEnable = True;
	AlphaTestEnable = False;
	SrcBlend = InvSrcAlpha;
	DestBlend = SrcAlpha;

	DitherEnable = True;
	zWriteEnable = True;
      	zEnable = True;
	CullMode = None;
	Lighting=True;		
	
	Ambient = mul(vecLight, ambientLightFactor);

	TextureTransformFlags[0] = Count2;		
	TextureTransform[0]= (matAlphaMapSize);
	texcoordindex[0]=0;
	ColorArg1[0] = Texture; 
        ColorOp[0] = SelectArg1;
        AlphaArg1[0] = Texture;
        AlphaOp[0] = SelectArg1;

	TextureTransformFlags[1] = Count2;		
	TextureTransform[1]= mul(matTerrainTexSize, Skin_Size3);
	texcoordindex[1]=1;

	ColorArg1[1] = Texture; 
	ColorArg2[1]= Diffuse;
        ColorOp[1] =Modulate;
        alphaarg1[1] = current;
        alphaop[1]=Disable;

      }

    pass p3
      {
	Sampler[0] 	= (s_RoadTex);   	// Blendmap is Alpha
	Sampler[1] 	= (s_RoadTex);     	// The Colormap 
	
	Lighting = True;
	Clipping=True;
	DitherEnable=True;
				
	AlphaBlendEnable = True;
	AlphaTestEnable = False;
	SrcBlend = InvsrcAlpha;
	DestBlend = SrcAlpha;

	DitherEnable = True;
	zWriteEnable = True;
      	zEnable = True;
	CullMode = None;
	Lighting=True;		
	
	Ambient = mul(vecLight, ambientLightFactor);

	TextureTransformFlags[0] = Count2;		
	TextureTransform[0]= (matAlphaMapSize);
	texcoordindex[0]=0;
	ColorArg1[0] = Texture; 
        ColorOp[0] = SelectArg1;
        AlphaArg1[0] = Texture;
        AlphaOp[0] = SelectArg1;

	TextureTransformFlags[1] = Count2;		
	TextureTransform[1]= mul(matTerrainTexSize, Skin_Size4);
	texcoordindex[1]=1;

	ColorArg1[1] = Texture; 
	ColorArg2[1]= Diffuse;
        ColorOp[1] =Modulate;
        alphaarg1[1] = current;
        alphaop[1]=Disable;

      }


   pass p4
      {
	Sampler[0] 	= (s_StoneTex);   	// Blendmap is Alpha
	Sampler[1] 	= (s_StoneTex);     	// The Colormap 
	
	Lighting = True;
	Clipping=True;
	DitherEnable=True;
	
	AlphaBlendEnable = True;
	AlphaTestEnable = False;
	SrcBlend = InvsrcAlpha;
	DestBlend = SrcAlpha;

	DitherEnable = True;
	zWriteEnable = True;
      	zEnable = True;
	CullMode = None;
	Lighting=True;		

	Ambient = mul(vecLight, ambientLightFactor);

	TextureTransformFlags[0] = Count2;		
	TextureTransform[0]= (matAlphaMapSize);
	texcoordindex[0]=0;
	ColorArg1[0] = Texture; 
        ColorOp[0] = SelectArg1;
        AlphaArg1[0] = Texture;
        AlphaOp[0] = SelectArg1;

	TextureTransformFlags[1] = Count2;		
	TextureTransform[1]= mul(matTerrainTexSize, Skin_Size5);
	texcoordindex[1]=1;

	ColorArg1[1] = Texture; 
	ColorArg2[1]= Diffuse;
        ColorOp[1] =Modulate;
        alphaarg1[1] = current;
        alphaop[1]=Disable;

      }
   
 }
