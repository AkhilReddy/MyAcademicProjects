using System.ComponentModel;

namespace BrainTechLLC.ThreadSafeObjects
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface ISupportsRemove<TKeyType>
   {
      bool Remove(TKeyType key);
   }
}
