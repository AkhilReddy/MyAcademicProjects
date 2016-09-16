using System;
using System.ComponentModel;

namespace BrainTechLLC.ThreadSafeObjects
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface ISuppliesID
   {
       long SuppliedID { get; set; }              
   }
}
