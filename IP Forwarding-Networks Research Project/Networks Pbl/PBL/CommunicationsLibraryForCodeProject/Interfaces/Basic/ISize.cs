using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface ISize : IVector4
   {
      float Length { get; set; }
      float Width { get; set; }
      float Height { get; set; }
   }
}
