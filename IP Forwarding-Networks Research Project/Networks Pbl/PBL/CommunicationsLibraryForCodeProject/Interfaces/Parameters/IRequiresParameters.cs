using System.ComponentModel;
using System.Collections.Generic;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IRequiresParameters
   {
      List<IParameterCategoryAndType> RequiredParameterTypes { get; }
   }
}
