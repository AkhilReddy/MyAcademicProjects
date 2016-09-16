using System.ComponentModel;

namespace BrainTechLLC.ThreadSafeObjects
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
	public interface ISupportsAddRemoveClear<TIndex, TListType> : ISupportsRemoveByIndex<TIndex, TListType>, ISupportsAddByIndex<TIndex, TListType>, ISupportsClear where TListType : class
   {
   }

   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface ISupportsAddRemoveClear<TListType> : ISupportsAdd<TListType>, ISupportsRemove<TListType>, ISupportsClear where TListType : class
   {
   }
}
