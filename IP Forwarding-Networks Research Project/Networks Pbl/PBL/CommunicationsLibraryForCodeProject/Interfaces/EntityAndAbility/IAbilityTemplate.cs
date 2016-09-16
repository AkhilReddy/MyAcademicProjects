using System.ComponentModel;
using BrainTechLLC.ThreadSafeObjects;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IAbilityTemplate : IHasClassTypeName, IHasTemplateID, ISuppliesID
   {      
      IAbility CreateAbilityFromTemplate(long entityID, IParameterCollection parameters);      
   }
}
