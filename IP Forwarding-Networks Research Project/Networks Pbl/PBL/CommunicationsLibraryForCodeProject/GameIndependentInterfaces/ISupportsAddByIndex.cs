using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface ISupportsAddByIndex<TIndex, TListType> where TListType : class
   {
      bool Add(TIndex key, TListType item);
   }
}
