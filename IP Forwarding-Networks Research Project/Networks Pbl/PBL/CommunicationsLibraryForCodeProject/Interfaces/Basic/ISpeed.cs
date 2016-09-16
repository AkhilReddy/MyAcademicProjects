using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface ISpeed : IVector4
   {
      bool Moving { get; }
      float SpeedX { get; set; }
      float SpeedY { get; set; }
      float SpeedZ { get; set; }
   }
}
