#pragma once

#include "AttributeSet.h"
#include "CoreMinimal.h"
#include "AeonAttributeSet.generated.h"

class UAeonAbilitySystemComponent;

/**
 * A macro to help define access to attributes.
 * Recommended practice in AttributeSet.h (Why is it not defined there?)
 *
 * Use <code>ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, Health)</code> to define the functions:
 *		static FGameplayAttribute GetHealthAttribute();
 *		float GetHealth() const;
 *		void SetHealth(float NewVal);
 *		void InitHealth(float NewVal);
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)           \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)               \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)               \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * The base AttributeSet in Aeon.
 */
UCLASS(Abstract, meta = (ShortTooltip = "The base AttributeSet used in Aeon."))
class AEON_API UAeonAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

protected:
    /**
     * Return the owning AeonAbilitySystemComponent.
     *
     * @return the owning AeonAbilitySystemComponent
     */
    UAeonAbilitySystemComponent* GetAeonAbilitySystemComponent() const;
};
