//Basic FX that simply transforms geometry from local space to homogeneous clip space and draws the geometry

//FX parameter(global to c++ app and this shader)

uniform extern float4x4 gWVP;
//uniform extern float4 color;

//Structure
struct OutputVS
{
	float4 posH:POSITION0;
	float4 color:COLOR0;
};

//Vertex Shader
OutputVS ColorVS(float3 posL:POSITION0,float4 c:COLOR0)
{
	//zERO OUT THE O/P
	OutputVS outVS=(OutputVS)0;

	//Transform to homogeneous clip space
	outVS.posH=mul(float4(posL,1.0f),gWVP);

	//Just pass the vertex color into the pixel shader
	outVS.color=c;

	//done return the o/p
	return outVS;
}

//Pixel SHader
float4 ColorPS(float4 c:COLOR0):COLOR
{
	//return float4(1.0f,0.0f,0.0f,1.0f);
	  return c;
}

technique TransformTech
{
	pass P0
	{
		//Specify the vertex and pixel shader associated with this pass
		vertexShader=compile vs_3_0 ColorVS();
		pixelShader=compile ps_3_0 ColorPS();

		//Specify render/ device states associated with this phase
		FillMode=Solid;	
}
}