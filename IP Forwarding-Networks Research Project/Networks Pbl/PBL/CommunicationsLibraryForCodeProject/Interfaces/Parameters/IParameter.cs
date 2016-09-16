using System;
using System.ComponentModel;
using BrainTechLLC.ThreadSafeObjects;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IParameter : ICloneable, IChanged, IHasClassTypeName, IHasType, IHasCategory, IQuickCopy<IParameter>, ISuppliesID 
   {
      long ParameterID { get; set; }
      IParameterValue ParameterValue { get; set; }

      string ParameterTypeName { get; }
      string ParameterCategoryName { get; }
   }
}
