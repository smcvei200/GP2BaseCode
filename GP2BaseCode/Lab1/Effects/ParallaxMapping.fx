float4x4 matWorld:WORLD < string UIWidget = "None";>;
float4x4 matView:VIEW < string UIWidget = "None";>;
float4x4 matProjection:PROJECTION < string UIWidget = "None";>;

float3 lightDirection: DIRECTION < string Object = "DirectionalLight";
									string UIWidget = "None";>;

float4 diffuseMaterial < string UIName = "Diffuse Material";
						 string UIWidget = "Color";
						 >;
						 
float4 diffuseLightColour: COLOR< 
						 string UIName = "Diffuse Light Colour";
						 string UIWidget = "None";
						 string Object = "DirectionalLight";
						 >;

float4 ambientMaterial < 
						 string UIName = "Ambient Material";
						 string UIWidget = "Color";
						 >;
float4 ambientLightColour < 
						 string UIName = "Ambient Light Colour";
						 string UIWidget = "Color";
						 >;
						 
float4 specularMaterial< string UIName = "Specular Material";
						 string UIWidget = "Color";
						 >;
						 
float4 specularLightColour< string UIName = "Specular Light Colour";
						 	string UIWidget = "Color";
						 	>;
						 
float4 cameraPosition: POSITION < string UIName = "Camera 1";
						 			string Object = "Perspective";
						 			>;

float power: POWER < string UIName = "Specular Power";
								float uimin = 0.0;
								float uimax = 20.0;
								float uistep = 0.01;
						 			string UIWidget = "Slider";
						 			>;

struct VS_INPUT
{
	float4 pos:POSITION;
	float3 normal:NORMAL;
	float3 tangent: TANGENT;
	float2 texCoord:TEXCOORD0;
};

struct PS_INPUT
{
	float4 pos:SV_POSITION;
	float3 normal:NORMAL;
	float3 viewDir: VIEWDIR;
	float3 lightDir: LIGHTDIR;
	float2 texCoord: TEXCOORD0;
};

Texture2D diffuseMap;
Texture2D bumpMap;
Texture2D heightMap;

SamplerState WrapPointSampler
{
	Filter = MIN_MAG_LINEAR_MIP_POINT;
	AddressU = Wrap;
	AddressV = Wrap;
};

PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output=(PS_INPUT)0;
	
	float4x4 matViewProjection=mul(matView,matProjection);
	float4x4 matWorldViewProjection=mul(matWorld,matViewProjection);
	
	float3x3 worldToTangent;
	worldToTangent[0] = mul(input.tangent,matWorld);
	worldToTangent[1] = mul(cross(input.tangent,input.normal),matWorld);
	worldToTangent[2] = mul(input.normal,matWorld);
	
	output.pos=mul(input.pos,matWorldViewProjection);
	output.normal = mul(input.normal, worldToTangent);
	
	float4 worldPos = mul(input.pos, matWorld);
	output.viewDir = mul((cameraPosition-worldPos.xyz),worldToTangent);
	output.lightDir = mul(lightDirection, worldToTangent);
	output.texCoord = input.texCoord;
	
	return output;
}

float4 PS(PS_INPUT input):SV_TARGET
{
	float scale = 0.03;
	float bias = 0.01;
	
	float heightVal = heightMap.Sample(WrapPointSampler, input.texCoord).x;
	float height = scale*heightVal-bias;
	
	float2 newTexCoord = height*input.viewDir.xy+input.texCoord;
	
	float3 normal = normalize((2*(bumpMap.Sample(WrapPointSampler, newTexCoord)))-1.0);
	//float3 normal=bumpMap.Sample(WrapPointSampler,input.texCoord);
	float3 lightDir = normalize(lightDirection);
	float diffuseHighlight = saturate(dot(normal,lightDir));
	float3 halfVec = normalize(lightDir+ input.viewDir);
	float specular = pow(saturate(dot(normal, halfVec)),power);
	float4 diffuseTextureColour= diffuseMap.Sample(WrapPointSampler,newTexCoord);
	//return float4(1.0f,1.0f,1.0f,1.0f);
	return (ambientMaterial*ambientLightColour)+((diffuseMaterial+diffuseTextureColour)*diffuseLightColour*diffuseHighlight)+(specularMaterial*specularLightColour*specular);
	//return diffuseTextureColour;
	}

RasterizerState DisableCulling
{
    CullMode = NONE;
};

technique10 Render
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_4_0, VS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0,  PS() ) );
		SetRasterizerState(DisableCulling); 
	}
}