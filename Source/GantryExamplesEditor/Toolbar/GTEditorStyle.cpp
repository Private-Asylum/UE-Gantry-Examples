// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Toolbar/GTEditorStyle.h"

#include "Framework/Application/SlateApplication.h"
#include "Misc/Paths.h"
#include "Styling/AppStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateTypes.h"

TSharedPtr<FSlateStyleSet> FGTEditorStyle::StyleInstance = nullptr;

void FGTEditorStyle::Initialize()
{
	if (StyleInstance.IsValid())
	{
		return;
	}

	StyleInstance = Create();
	FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
}

void FGTEditorStyle::Shutdown()
{
	if (!StyleInstance.IsValid())
	{
		return;
	}

	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FGTEditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("GantryExamplesEditorStyle"));
	return StyleSetName;
}

const ISlateStyle& FGTEditorStyle::Get()
{
	return *StyleInstance;
}

void FGTEditorStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

TSharedRef<FSlateStyleSet> FGTEditorStyle::Create()
{
	TSharedRef<FSlateStyleSet> Style = MakeShared<FSlateStyleSet>(GetStyleSetName());

	// Project artwork goes here. Nothing reads from it yet, but having the root set means adding
	// an SVG later is a one-line change.
	Style->SetContentRoot(FPaths::ProjectContentDir() / TEXT("Editor/Slate"));

	// Text style used by the project's menu section headers.
	const FTextBlockStyle NormalText = FAppStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText");

	FTextBlockStyle SectionHeader = NormalText;
	SectionHeader.SetColorAndOpacity(FSlateColor(FLinearColor(0.72f, 0.72f, 0.72f)));

	Style->Set("GantryExamplesEditor.SectionHeader", SectionHeader);

	return Style;
}
