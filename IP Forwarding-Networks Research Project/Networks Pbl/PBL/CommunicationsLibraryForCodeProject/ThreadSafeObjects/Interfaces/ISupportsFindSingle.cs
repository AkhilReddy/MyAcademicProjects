﻿using System.Collections.Generic;
using System.ComponentModel;

namespace BrainTechLLC.ThreadSafeObjects
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface ISupportsFindSingle<TIndex, TListType> where TListType : class
   {
      TListType FindSingle(TIndex key);
   }
}
