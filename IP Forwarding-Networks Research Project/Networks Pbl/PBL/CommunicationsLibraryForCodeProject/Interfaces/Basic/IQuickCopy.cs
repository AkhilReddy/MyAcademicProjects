using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IQuickCopy
   {
      object Copy();
   }

   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IQuickCopy<T> where T : class
   {
      T Copy();
   }
}
