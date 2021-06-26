using Lab10.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.AspNetCore.Authorization;
using System.Threading.Tasks;

// For more information on enabling Web API for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace Lab10.Controllers
{
    [Authorize]
    [Route("api/[controller]")]
    [ApiController]
    public class FilterController : ControllerBase
    {
        private readonly UserContext _context;

        public FilterController(UserContext context)
        {
            _context = context;
        }

        // GET: api/<FilterController>
        [HttpGet("{role}")]
        public async Task<ActionResult<IEnumerable<User>>> Get(string role)
        {
            return await _context.Users.Where(u => u.Role == role).ToListAsync();
        }

    }
}
