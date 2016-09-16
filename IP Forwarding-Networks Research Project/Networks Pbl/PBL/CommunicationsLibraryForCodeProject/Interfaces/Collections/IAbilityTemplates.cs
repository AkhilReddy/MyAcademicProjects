using System.ComponentModel;
using BrainTechLLC.ThreadSafeObjects;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
	public interface IAbilityTemplates : IMultipleItems<IAbilityTemplate>, ISupportsAddRemoveClear<long, IAbilityTemplate>, ISupportsCount, ISupportsFindMany<long, IAbilityTemplate>
   {
   }
}
