using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IFromTemplate<T> where T : class 
   {
      T Template { get; set; }
   }
}
