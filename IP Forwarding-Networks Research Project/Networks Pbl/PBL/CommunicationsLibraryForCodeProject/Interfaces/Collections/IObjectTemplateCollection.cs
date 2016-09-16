using System.Collections.Generic;
using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IObjectTemplateCollection : ISupportsAdd<long>, ISupportsRemove<long>
   {
      List<long> AllObjectTemplates { get; }
   }
}
