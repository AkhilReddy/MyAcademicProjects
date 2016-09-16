﻿using System.ComponentModel;

namespace BrainTechLLC.ThreadSafeObjects
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface ISupportsAddByIndex<TIndex, TListType> where TListType : class
   {
      bool Add(TIndex key, TListType item);
   }
}
