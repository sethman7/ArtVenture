// Oyintare Ebelo 2023.

using UnrealBuildTool;
using System.IO;

public class ElevenWave : ModuleRules
{
	public ElevenWave(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		

		AddEngineThirdPartyPrivateStaticDependencies(Target,
			"UEOgg"
		);
		
		PublicDefinitions.AddRange(
			new string[]
			{
				"DR_MP3_IMPLEMENTATION=1",
			}
		);
		
		if (Target.Version.MajorVersion >= 5 && Target.Version.MinorVersion >= 2)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"AudioExtensions"
				}
			);
		}
		
		PublicIncludePaths.AddRange(
			new string[] {
				"ThirdParty"
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"ThirdParty"
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "CoreUObject", "Engine","HTTP","Json", "JsonUtilities", "DeveloperSettings"/*,"DR_MP3_IMPLEMENTATION=1"*/
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"AudioPlatformConfiguration",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
