using MonsterDropWebAPI.Services;
using MonsterDropWebAPI.Hubs;
using Microsoft.OpenApi.Models;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container
builder.Services.AddControllers();
builder.Services.AddEndpointsApiExplorer();

// Configure Swagger/OpenAPI
builder.Services.AddSwaggerGen(c =>
{
    c.SwaggerDoc("v1", new OpenApiInfo
    {
        Title = "Shaiya Monster Drop Web API",
        Version = "v1",
        Description = "Web API for managing Shaiya Episode 6 monster drop rates in real-time",
        Contact = new OpenApiContact
        {
            Name = "Shaiya Community",
            Url = new Uri("https://github.com/nonigagalac/shaiya-episode-6")
        }
    });

    // Include XML comments if available
    var xmlFile = $"{System.Reflection.Assembly.GetExecutingAssembly().GetName().Name}.xml";
    var xmlPath = Path.Combine(AppContext.BaseDirectory, xmlFile);
    if (File.Exists(xmlPath))
    {
        c.IncludeXmlComments(xmlPath);
    }
});

// Add CORS
builder.Services.AddCors(options =>
{
    options.AddPolicy("AllowWebApp", policy =>
    {
        policy.WithOrigins("http://localhost:3000", "http://localhost:5173", "https://localhost:3000", "https://localhost:5173")
              .AllowAnyHeader()
              .AllowAnyMethod()
              .AllowCredentials();
    });
});

// Add SignalR
builder.Services.AddSignalR(options =>
{
    options.EnableDetailedErrors = true;
    options.KeepAliveInterval = TimeSpan.FromSeconds(15);
    options.ClientTimeoutInterval = TimeSpan.FromSeconds(30);
});

// Add memory caching
builder.Services.AddMemoryCache();

// Add custom services
builder.Services.AddSingleton<MemoryService>();
builder.Services.AddSingleton<NotificationService>();

// Add logging
builder.Services.AddLogging(logging =>
{
    logging.ClearProviders();
    logging.AddConsole();
    logging.AddDebug();
    if (builder.Environment.IsDevelopment())
    {
        logging.SetMinimumLevel(LogLevel.Debug);
    }
});

var app = builder.Build();

// Configure the HTTP request pipeline
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI(c =>
    {
        c.SwaggerEndpoint("/swagger/v1/swagger.json", "Monster Drop API v1");
        c.RoutePrefix = "swagger";
        c.DisplayRequestDuration();
        c.EnableTryItOutByDefault();
    });
}

// Enable CORS
app.UseCors("AllowWebApp");

// Add security headers
app.Use(async (context, next) =>
{
    context.Response.Headers.Add("X-Content-Type-Options", "nosniff");
    context.Response.Headers.Add("X-Frame-Options", "DENY");
    context.Response.Headers.Add("X-XSS-Protection", "1; mode=block");
    context.Response.Headers.Add("Referrer-Policy", "strict-origin-when-cross-origin");
    
    await next();
});

app.UseRouting();
app.UseAuthorization();

app.MapControllers();

// Map SignalR hub
app.MapHub<MonsterDropHub>("/hubs/monsterdrop");

// Setup MemoryService event handlers
var memoryService = app.Services.GetRequiredService<MemoryService>();
var notificationService = app.Services.GetRequiredService<NotificationService>();

memoryService.MobUpdated += async (sender, mob) =>
{
    await notificationService.BroadcastMobUpdateAsync(mob);
};

memoryService.StatusChanged += async (sender, status) =>
{
    await notificationService.BroadcastSystemStatusAsync(status);
};

memoryService.ProcessDetached += async (sender, processName) =>
{
    await notificationService.BroadcastProcessDetachedAsync(processName);
};

// Add default route
app.MapGet("/", () => new
{
    Name = "Shaiya Monster Drop Web API",
    Version = "1.0.0",
    Description = "Web API for managing Shaiya Episode 6 monster drop rates",
    Endpoints = new
    {
        Swagger = "/swagger",
        Health = "/api/system/health",
        SignalR = "/hubs/monsterdrop"
    },
    Links = new
    {
        GitHub = "https://github.com/nonigagalac/shaiya-episode-6",
        Documentation = "/swagger"
    }
});

// Global exception handler
app.UseExceptionHandler(errorApp =>
{
    errorApp.Run(async context =>
    {
        var logger = context.RequestServices.GetRequiredService<ILogger<Program>>();
        var exception = context.Features.Get<Microsoft.AspNetCore.Diagnostics.IExceptionHandlerFeature>()?.Error;
        
        if (exception != null)
        {
            logger.LogError(exception, "Unhandled exception occurred");
        }

        context.Response.StatusCode = 500;
        context.Response.ContentType = "application/json";

        var response = new
        {
            Success = false,
            Message = "An internal server error occurred",
            Timestamp = DateTime.UtcNow
        };

        await context.Response.WriteAsync(System.Text.Json.JsonSerializer.Serialize(response));
    });
});

var logger = app.Services.GetRequiredService<ILogger<Program>>();
logger.LogInformation("Shaiya Monster Drop Web API is starting...");

try
{
    app.Run();
}
catch (Exception ex)
{
    logger.LogCritical(ex, "Application terminated unexpectedly");
    throw;
}
finally
{
    // Cleanup
    memoryService?.Dispose();
}