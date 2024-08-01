# Coursework for "Unreal Engine 5 C++: Advanced Action RPG"

This the project developed in the course [Unreal Engine 5 C++: Advanced Action RPG](https://www.udemy.com/course/unreal-engine-5-advanced-action-rpg/).

# Actions to Consider

* Convert `GA_Shared_SpawnWeapon` to C++ so that we can add better validation rules (ala `meta=(RuleRangerRequired="true")`)
* Consider supporting `meta=(RuleRangerRequired="MyComponent.MyProperty,MyOtherComponent.Property2")` to `UCLASS()` and this would error if the component/property is missing, of the wrong type or has a null reference. This would be inherited from superclasses. The intent is the ability to declare a requirement for a reference to exist even if the user does not author the component. 
