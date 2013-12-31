////////////////////////////////////////////////////////
//all entities that set to this material render in black
//--------------------Xd1vo-----------------------------
////////////////////////////////////////////////////////

texture entSkin1;

technique black
{
	pass p0
	{
		AlphaBlendEnable=True;  
		Zenable = True;
		ZwriteEnable = True;
		BlendOp=Add;
		Lighting=False;
		
		FogEnable = True;
		FogColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
		FogStart = 60000;
		FogEnd = 50000;
		
		
		ShadeMode = Flat;
		Texture[0] = <entSkin1>;
		ColorArg1[0] = Diffuse;
		ColorOp[0] = SelectArg1;
	}
}
