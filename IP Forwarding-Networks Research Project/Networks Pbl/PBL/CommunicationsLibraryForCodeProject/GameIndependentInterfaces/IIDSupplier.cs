using System;
using System.ComponentModel;

namespace BrainTechLLC.EmlenMud.Interfaces
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface IIDSupplier 
   {
       long GetNextId();
       long CurrentMaxId { get; set; }
       
   }
}
