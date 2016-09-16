using System;
using System.ComponentModel;

namespace BrainTechLLC.ThreadSafeObjects
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface ILockable
   {
       void AquireLock();
       void ReleaseLock();
       bool Locked { get; }
       bool TryAquireLock();
   }
}
