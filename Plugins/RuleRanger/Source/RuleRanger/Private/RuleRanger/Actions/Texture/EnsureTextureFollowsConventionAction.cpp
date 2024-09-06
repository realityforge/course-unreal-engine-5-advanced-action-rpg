/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "EnsureTextureFollowsConventionAction.h"
#include "Subsystems/EditorAssetSubsystem.h"

void UEnsureTextureFollowsConventionAction::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    const FName PropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;
    // ReSharper disable once CppTooWideScopeInitStatement
    const FName TableName = GET_MEMBER_NAME_CHECKED(UEnsureTextureFollowsConventionAction, ConventionsTables);
    if (TableName == PropertyName)
    {
        ResetConventionsCache();
    }
    Super::PostEditChangeProperty(PropertyChangedEvent);
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void UEnsureTextureFollowsConventionAction::ResetCacheIfTableModified(UObject* Object)
{
    // This is called on any object edit in editor so match against conventions tables and bust cache as appropriate;
    if (Object && ConventionsTables.Contains(Object))
    {
        ResetConventionsCache();
    }
}

void UEnsureTextureFollowsConventionAction::ResetConventionsCache()
{
    LogInfo(nullptr, TEXT("Resetting the Conventions Cache"));

    ConventionsCache.Empty();
    FCoreUObjectDelegates::OnObjectModified.Remove(OnObjectModifiedDelegateHandle);
    OnObjectModifiedDelegateHandle.Reset();
}

void UEnsureTextureFollowsConventionAction::RebuildConventionsCacheIfNecessary()
{
    check(!ConventionsTables.IsEmpty());

    bool bTableDataPresent = false;
    for (const auto& ConventionsTable : ConventionsTables)
    {
        if (0 != ConventionsTable->GetTableData().Num())
        {
            bTableDataPresent = true;
            break;
        }
    }
    if (bTableDataPresent)
    {
        ResetConventionsCache();
        // Add a callback for when ANY object is modified in the editor so that we can bust the cache
        OnObjectModifiedDelegateHandle = FCoreUObjectDelegates::OnObjectModified.AddUObject(
            this,
            &UEnsureTextureFollowsConventionAction::ResetCacheIfTableModified);
        for (const auto& ConventionsTable : ConventionsTables)
        {
            for (const auto& RowName : ConventionsTable->GetRowNames())
            {
                if (const auto& Convention = ConventionsTable->FindRow<FRuleRangerTextureConvention>(RowName, TEXT("")))
                {
                    ConventionsCache.Emplace(RowName, *Convention);
                }
            }
        }
    }
}

void UEnsureTextureFollowsConventionAction::CheckPowerOfTwo(URuleRangerActionContext* ActionContext,
                                                            const UTexture2D* const Texture) const
{
    const int32 SizeX = Texture->GetSizeX();
    const int32 SizeY = Texture->GetSizeY();

    const bool bInvalidX = (0 != (SizeX & SizeX - 1));
    const bool bInvalidY = (0 != (SizeY & SizeY - 1));

    if (bInvalidX || bInvalidY)
    {
        FFormatNamedArguments Arguments;
        Arguments.Add(TEXT("X"), FText::FromString(FString::FromInt(SizeX)));
        Arguments.Add(TEXT("Y"), FText::FromString(FString::FromInt(SizeY)));

        if (bInvalidX && bInvalidY)
        {
            const FText Message = FText::Format(NSLOCTEXT("RuleRanger",
                                                          "EnsureTextureFollowsConventionAction_Pow2FailXY",
                                                          "Texture has dimensions {X}x{Y} and neither width nor"
                                                          " height is a power of two. Fix both dimensions"),
                                                Arguments);
            ActionContext->Error(Message);
        }
        else if (bInvalidX)
        {
            const FText Message = FText::Format(
                NSLOCTEXT("RuleRanger",
                          "EnsureTextureFollowsConventionAction_Pow2FailX",
                          "Texture has dimensions {X}x{Y} and width is not a power of two. Fix the width dimension"),
                Arguments);
            ActionContext->Error(Message);
        }
        else
        {
            const FText Message = FText::Format(
                NSLOCTEXT("RuleRanger",
                          "EnsureTextureFollowsConventionAction_Pow2FailY",
                          "Texture has dimensions {X}x{Y} and height is not a power of two. Fix the height dimension"),
                Arguments);
            ActionContext->Error(Message);
        }
    }
    else
    {
        LogInfo(Texture, TEXT("Texture dimensions are a power of two. No Action required."));
    }
}

void UEnsureTextureFollowsConventionAction::CheckDivisibleConstraint(URuleRangerActionContext* ActionContext,
                                                                     const ETextureResolutionConstraint Constraint,
                                                                     const UTexture2D* const Texture) const
{
    const int Divisor = ETextureResolutionConstraint::DivisibleByFour == Constraint ? 4
        : ETextureResolutionConstraint::DivisibleByEight == Constraint              ? 8
                                                                                    : 12;
    const int32 SizeX = Texture->GetSizeX();
    const int32 SizeY = Texture->GetSizeY();

    const bool bInvalidX = 0 != (SizeX % Divisor);
    const bool bInvalidY = 0 != (SizeY % Divisor);

    if (bInvalidX || bInvalidY)
    {
        FFormatNamedArguments Arguments;
        Arguments.Add(TEXT("X"), FText::FromString(FString::FromInt(SizeX)));
        Arguments.Add(TEXT("Y"), FText::FromString(FString::FromInt(SizeY)));
        Arguments.Add(TEXT("Divisor"), FText::FromString(FString::FromInt(Divisor)));

        if (bInvalidX && bInvalidY)
        {
            const FText Message = FText::Format(NSLOCTEXT("RuleRanger",
                                                          "EnsureTextureFollowsConventionAction_DivFailXY",
                                                          "Texture has dimensions {X}x{Y} and neither width nor"
                                                          " height is divisible by {Divisor}. Fix both dimensions"),
                                                Arguments);
            ActionContext->Error(Message);
        }
        else if (bInvalidX)
        {
            const FText Message = FText::Format(NSLOCTEXT("RuleRanger",
                                                          "EnsureTextureFollowsConventionAction_DivFailX",
                                                          "Texture has dimensions {X}x{Y} and width is not "
                                                          "divisible by {Divisor}. Fix the width dimension"),
                                                Arguments);
            ActionContext->Error(Message);
        }
        else
        {
            const FText Message = FText::Format(NSLOCTEXT("RuleRanger",
                                                          "EnsureTextureFollowsConventionAction_DivFailY",
                                                          "Texture has dimensions {X}x{Y} and height is not "
                                                          "divisible by {Divisor}. Fix the height dimension"),
                                                Arguments);
            ActionContext->Error(Message);
        }
    }
    else
    {
        LogInfo(Texture, FString::Printf(TEXT("Texture dimensions are divisible by %d. No Action required."), Divisor));
    }
}

void UEnsureTextureFollowsConventionAction::PerformTextureResolutionConstraintCheck(
    URuleRangerActionContext* ActionContext,
    const FRuleRangerTextureConvention* const Convention,
    const UTexture2D* const Texture) const
{
    if (ETextureResolutionConstraint::PowerOfTwo == Convention->TextureResolutionConstraint)
    {
        CheckPowerOfTwo(ActionContext, Texture);
    }
    else if (ETextureResolutionConstraint::Auto != Convention->TextureResolutionConstraint)
    {
        CheckDivisibleConstraint(ActionContext, Convention->TextureResolutionConstraint, Texture);
    }
}

void UEnsureTextureFollowsConventionAction::PerformTextureGroupCheck(URuleRangerActionContext* ActionContext,
                                                                     const UObject* Object,
                                                                     FRuleRangerTextureConvention* const Convention,
                                                                     UTexture2D* const Texture) const
{
    if (!Convention->TextureGroups.IsEmpty() && !Convention->TextureGroups.Contains(Texture->LODGroup))
    {
        const UEnum* Enum = StaticEnum<TextureGroup>();
        if (bApplyFix && Convention->TextureGroups.Num() > 0)
        {
            FFormatNamedArguments Arguments;
            Arguments.Add(TEXT("OriginalGroup"), Enum->GetDisplayNameTextByValue(Texture->CompressionSettings));
            Arguments.Add(TEXT("NewGroup"), Enum->GetDisplayNameTextByValue(Convention->TextureGroups[0]));
            if (ActionContext->IsDryRun())
            {
                const FText Message = FText::Format(NSLOCTEXT("RuleRanger",
                                                              "TextureCompressionChangeOmitted",
                                                              "Texture should have the TextureGroup changed from "
                                                              "'{OriginalGroup}' to '{NewGroup}'. "
                                                              "Action skipped in DryRun mode"),
                                                    Arguments);
                ActionContext->Warning(Message);
            }
            else
            {
                const FText Message = FText::Format(NSLOCTEXT("RuleRanger",
                                                              "TextureGroupChanged",
                                                              "Texture changed the TextureGroup from "
                                                              "'{OriginalGroup}' to '{NewGroup}'"),
                                                    Arguments);
                ActionContext->Info(Message);

                Texture->LODGroup = Convention->TextureGroups[0];

                ensure(Object->MarkPackageDirty());
                ensure(Object->GetOuter()->MarkPackageDirty());
            }
        }
        else
        {
            FString ValidGroups{ "" };
            for (const auto& Group : Convention->TextureGroups)
            {
                if (ValidGroups.Len() > 0)
                {
                    ValidGroups.Append(", ");
                }
                ValidGroups.Append(Enum->GetDisplayNameTextByValue(Group).ToString());
            }
            FFormatNamedArguments Arguments;
            Arguments.Add(TEXT("ActualGroup"), Enum->GetDisplayNameTextByValue(Texture->LODGroup));
            Arguments.Add(TEXT("ValidGroups"), FText::FromString(ValidGroups));
            const FText Message = FText::Format(NSLOCTEXT("RuleRanger",
                                                          "EnsureTextureGroupValidAction_Fail",
                                                          "Texture has the TextureGroup '{ActualGroup}' that is not "
                                                          "one of the valid TextureGroups: '{ValidGroups}'"),
                                                Arguments);
            ActionContext->Error(Message);
        }
    }
    else
    {
        LogInfo(Texture, TEXT("Texture has a valid TextureGroup. No Action required."));
    }
}

void UEnsureTextureFollowsConventionAction::PerformColorSpaceCheck(URuleRangerActionContext* ActionContext,
                                                                   const UObject* Object,
                                                                   const FRuleRangerTextureConvention* const Convention,
                                                                   UTexture2D* const Texture) const
{
    if (ERuleRangerTextureColorSpace::Auto != Convention->ColorSpace)
    {
        // ReSharper disable once CppTooWideScopeInitStatement
        const bool bSRGB = Convention->ColorSpace == ERuleRangerTextureColorSpace::SRGB;
        if (Texture->SRGB != bSRGB)
        {
            FFormatNamedArguments Arguments;
            Arguments.Add(TEXT("Original"), FText::FromString(bSRGB ? TEXT("false") : TEXT("true")));
            Arguments.Add(TEXT("New"), FText::FromString(bSRGB ? TEXT("true") : TEXT("false")));
            if (ActionContext->IsDryRun())
            {
                const FText Message = FText::Format(NSLOCTEXT("RuleRanger",
                                                              "TextureSRGBChangeOmitted",
                                                              "Texture should have sRGB changed from "
                                                              "'{Original}' to '{New}'. "
                                                              "Action skipped in DryRun mode"),
                                                    Arguments);
                ActionContext->Warning(Message);
            }
            else
            {
                const FText Message = FText::Format(
                    NSLOCTEXT("RuleRanger", "TextureSRGBChanged", "Texture changed sRGB from '{Original}' to '{New}'"),
                    Arguments);
                ActionContext->Info(Message);

                Texture->SRGB = bSRGB;

                ensure(Object->MarkPackageDirty());
                ensure(Object->GetOuter()->MarkPackageDirty());
            }
        }
        else
        {
            LogInfo(Texture, TEXT("Texture has a valid sRGB. No Action required."));
        }
    }
}

void UEnsureTextureFollowsConventionAction::PerformMipGenSettingsCheck(
    URuleRangerActionContext* ActionContext,
    const UObject* Object,
    const FRuleRangerTextureConvention* const Convention,
    UTexture2D* const Texture) const
{
    if (!Convention->TextureMipGenSettings.IsEmpty()
        && !Convention->TextureMipGenSettings.Contains(Texture->MipGenSettings))
    {
        const UEnum* Enum = StaticEnum<TextureMipGenSettings>();
        if (bApplyFix && Convention->TextureMipGenSettings.Num() > 0)
        {
            FFormatNamedArguments Arguments;
            Arguments.Add(TEXT("OriginalSetting"), Enum->GetDisplayNameTextByValue(Texture->MipGenSettings));
            Arguments.Add(TEXT("NewSetting"), Enum->GetDisplayNameTextByValue(Convention->TextureMipGenSettings[0]));
            if (ActionContext->IsDryRun())
            {
                const FText Message = FText::Format(NSLOCTEXT("RuleRanger",
                                                              "TextureMipGenChangeOmitted",
                                                              "Texture should have the MipGen setting changed from "
                                                              "'{OriginalSetting}' to '{NewSetting}'. "
                                                              "Action skipped in DryRun mode"),
                                                    Arguments);
                ActionContext->Warning(Message);
            }
            else
            {
                const FText Message = FText::Format(NSLOCTEXT("RuleRanger",
                                                              "TextureMipGenChanged",
                                                              "Texture changed the compression setting from "
                                                              "'{OriginalSetting}' to '{NewSetting}'"),
                                                    Arguments);
                ActionContext->Info(Message);

                Texture->MipGenSettings = Convention->TextureMipGenSettings[0];

                ensure(Object->MarkPackageDirty());
                ensure(Object->GetOuter()->MarkPackageDirty());
            }
        }
        else
        {
            FString ValidSettings{ "" };
            for (const auto& Setting : Convention->TextureMipGenSettings)
            {
                if (ValidSettings.Len() > 0)
                {
                    ValidSettings.Append(", ");
                }
                ValidSettings.Append(Enum->GetDisplayNameTextByValue(Setting).ToString());
            }
            FFormatNamedArguments Arguments;
            Arguments.Add(TEXT("ActualSettings"), Enum->GetDisplayNameTextByValue(Texture->MipGenSettings));
            Arguments.Add(TEXT("ValidSettings"), FText::FromString(ValidSettings));
            const FText Message =
                FText::Format(NSLOCTEXT("RuleRanger",
                                        "EnsureTextureMipGenValidAction_Fail",
                                        "Texture has the MipGen setting '{ActualSettings}' that is not "
                                        "one of the valid MipGen settings '{ValidSettings}' and the "
                                        "ApplyFix action parameter has not been specified"),
                              Arguments);
            ActionContext->Error(Message);
        }
    }
    else
    {
        LogInfo(Texture, TEXT("Texture has a valid MipGen Setting. No Action required."));
    }
}

void UEnsureTextureFollowsConventionAction::PerformTextureCompressionCheck(
    URuleRangerActionContext* ActionContext,
    const UObject* Object,
    FRuleRangerTextureConvention* const Convention,
    UTexture2D* const Texture) const
{
    if (!Convention->TextureCompressionSettings.IsEmpty()
        && !Convention->TextureCompressionSettings.Contains(Texture->CompressionSettings))
    {
        const UEnum* Enum = StaticEnum<TextureCompressionSettings>();
        if (bApplyFix && Convention->TextureCompressionSettings.Num() > 0)
        {
            FFormatNamedArguments Arguments;
            Arguments.Add(TEXT("OriginalSetting"), Enum->GetDisplayNameTextByValue(Texture->CompressionSettings));
            Arguments.Add(TEXT("NewSetting"),
                          Enum->GetDisplayNameTextByValue(Convention->TextureCompressionSettings[0]));
            if (ActionContext->IsDryRun())
            {
                const FText Message =
                    FText::Format(NSLOCTEXT("RuleRanger",
                                            "TextureCompressionChangeOmitted",
                                            "Texture should have the compression setting changed from "
                                            "'{OriginalSetting}' to '{NewSetting}'. "
                                            "Action skipped in DryRun mode"),
                                  Arguments);
                ActionContext->Warning(Message);
            }
            else
            {
                const FText Message = FText::Format(NSLOCTEXT("RuleRanger",
                                                              "TextureCompressionChanged",
                                                              "Texture changed the compression setting from "
                                                              "'{OriginalSetting}' to '{NewSetting}'"),
                                                    Arguments);
                ActionContext->Info(Message);

                Texture->CompressionSettings = Convention->TextureCompressionSettings[0];

                ensure(Object->MarkPackageDirty());
                ensure(Object->GetOuter()->MarkPackageDirty());
            }
        }
        else
        {
            FString ValidSettings{ "" };
            for (const auto& Setting : Convention->TextureCompressionSettings)
            {
                if (ValidSettings.Len() > 0)
                {
                    ValidSettings.Append(", ");
                }
                ValidSettings.Append(Enum->GetDisplayNameTextByValue(Setting).ToString());
            }
            FFormatNamedArguments Arguments;
            Arguments.Add(TEXT("ActualSettings"), Enum->GetDisplayNameTextByValue(Texture->CompressionSettings));
            Arguments.Add(TEXT("ValidSettings"), FText::FromString(ValidSettings));
            const FText Message = FText::Format(NSLOCTEXT("RuleRanger",
                                                          "EnsureTextureCompressionValidAction_Fail",
                                                          "Texture has the compression '{ActualSettings}' that is not "
                                                          "one of the valid Texture Compressions '{ValidSettings}' and "
                                                          "ApplyFix action parameter has not been specified"),
                                                Arguments);
            ActionContext->Error(Message);
        }
    }
    else
    {
        LogInfo(Texture, TEXT("Texture has a valid Texture Compression Setting. No Action required."));
    }
}

void UEnsureTextureFollowsConventionAction::Apply_Implementation(URuleRangerActionContext* ActionContext,
                                                                 UObject* Object)
{
    const auto Texture = CastChecked<UTexture2D>(Object);

    const auto Subsystem = GEditor->GetEditorSubsystem<UEditorAssetSubsystem>();
    const auto Variant = Subsystem ? Subsystem->GetMetadataTag(Object, FName("RuleRanger.Variant")) : TEXT("");

    if (!ConventionsTables.IsEmpty())
    {
        RebuildConventionsCacheIfNecessary();

        if (const auto Convention = ConventionsCache.Find(FName(Variant)))
        {
            PerformTextureCompressionCheck(ActionContext, Object, Convention, Texture);
            PerformColorSpaceCheck(ActionContext, Object, Convention, Texture);
            PerformTextureGroupCheck(ActionContext, Object, Convention, Texture);
            PerformTextureResolutionConstraintCheck(ActionContext, Convention, Texture);
            PerformMipGenSettingsCheck(ActionContext, Object, Convention, Texture);
        }
    }
}
