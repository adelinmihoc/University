﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Lab10
{
    public interface IJwtAuthenticationManager
    {
        string Authenticate(string username);
    }
}
