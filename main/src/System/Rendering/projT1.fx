////////////////////////////////////////////////////////
// Projected texture (FFP) by Xd1Vo
////////////////////////////////////////////////////////

float4x4 matEffect1;

texture mtlSkin1;
texture mtlSkin2;
texture entSkin1;

technique proj_tex
{
	pass p0
	{
		
		Texture[0] = <entSkin1>;
		Texture[1] = <mtlSkin1>; // projected
		
		ColorArg1[0] = Texture;
		ResultArg[0] = Temp;
		
		ColorArg2[1] = Texture;
		ColorArg1[1] = Diffuse;
		ColorOp[1] = AddSigned2x;
		
		ColorArg1[2] = Current;
		ColorArg2[2] = Temp;
		ColorOp[2] = Modulate;
		
		
		TexCoordIndex[0] = 1;
		AddressU[1] = BORDER;
		AddressV[1] = BORDER;
		BorderColor[1] = 0xffffff;  
		
		texcoordindex[1] = cameraspaceposition ; 
		TextureTransformFlags[1] = count3 | projected;
		TextureTransform[1] = <matEffect1>;
		
	}
}
