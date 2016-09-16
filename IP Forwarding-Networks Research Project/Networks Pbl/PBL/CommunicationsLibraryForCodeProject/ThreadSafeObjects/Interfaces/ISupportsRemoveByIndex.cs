using System.ComponentModel;

namespace BrainTechLLC.ThreadSafeObjects
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface ISupportsRemoveByIndex<TIndex, TListType> where TListType : class
   {
      bool Remove(TIndex key, TListType item);
   }
}
