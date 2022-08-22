// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class MedurvalEditorTarget : TargetRules
{
	public MedurvalEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Settlements" } );
		ExtraModuleNames.AddRange( new string[] { "Medurval" } );
	}
}
