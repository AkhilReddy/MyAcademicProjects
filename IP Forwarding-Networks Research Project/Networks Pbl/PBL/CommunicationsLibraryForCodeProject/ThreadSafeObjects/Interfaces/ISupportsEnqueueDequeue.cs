using System.ComponentModel;

namespace BrainTechLLC.ThreadSafeObjects
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface ISupportsEnqueueDequeue<TListType> 
   {
      void Enqueue(TListType item);
      bool Dequeue(out TListType item);
   }   
}
