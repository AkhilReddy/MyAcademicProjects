using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface ISingleAction : IHasAssociatedID, IHasFriendlyName 
   {
      bool CanPerformAction(IIntention intention, IParameterCollection parameters);
      bool DoBasePerformAction(IIntention intention, IParameterCollection parameters);      
      ISingleAction CreateInstance(long ID);      
   }
}
