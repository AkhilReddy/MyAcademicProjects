using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IPerformsInitialization
   {
      bool Initialize(ITypeLookup typeLookup);      
   }
}
