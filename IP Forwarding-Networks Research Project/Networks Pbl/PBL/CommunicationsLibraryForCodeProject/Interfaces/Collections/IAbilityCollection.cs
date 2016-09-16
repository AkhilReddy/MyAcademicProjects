using System.Collections.Generic;
using System.ComponentModel;
using BrainTechLLC.ThreadSafeObjects;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IAbilityCollection : ISupportsCount, IMultipleItems<IAbility>, ISupportsAddRemoveClear<IAbility>
   {
      bool UnsafeAdd(IAbility ability);
      IIntention FindAvailableIntention(int intentionType, out IAbility ability);
      IIntention FindAvailableIntention(int intentionType, long abilityID, out IAbility ability);            
      List<IAbility> GetAbilitiesOfType(int abilityType);
      List<IAbility> GetAbilitiesOfType(string abilityTypeName);
      List<IAbility> GetAbilities(string abilityClassName);
   }
}
