using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IDirection : IVector4
   {
      IDirection DirectionVector { get; }      
   }
}
