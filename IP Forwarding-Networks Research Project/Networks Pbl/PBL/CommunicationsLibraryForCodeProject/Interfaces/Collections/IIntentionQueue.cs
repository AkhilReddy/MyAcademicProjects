using System.ComponentModel;
using BrainTechLLC.ThreadSafeObjects;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IIntentionQueue : IMultipleItems<IIntention>, ISupportsAdd<IIntention>, ISupportsClear, ISupportsCount
   {
      IIntention Dequeue();
      void Set(IIntention intention);
   }
}
