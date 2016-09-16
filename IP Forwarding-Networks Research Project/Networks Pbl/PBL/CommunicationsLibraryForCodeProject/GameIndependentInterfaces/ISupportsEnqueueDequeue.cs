using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface ISupportsEnqueueDequeue<TListType> 
   {
      void Enqueue(TListType item);
      bool Dequeue(out TListType item);
   }   
}
