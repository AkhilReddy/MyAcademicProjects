﻿using System.Collections.Generic;
using System.ComponentModel;

namespace BrainTechLLC.ThreadSafeObjects
{
   [Browsable(true), TypeConverter(typeof(ExpandableObjectConverter))]
   public interface ISupportsFindMany<TIndex, TListType> : ISupportsFindSingle<TIndex, TListType> where TListType : class
   {
      List<TListType> Find(TIndex key);
   }
}
