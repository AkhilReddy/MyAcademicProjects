using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IDynamicEnumEntry
   {
      IDynamicEnum BelongsTo { get; set; }
      string Name { get; set; }
      int Value { get; set; }
      string Description { get; set; }      
   }
}
