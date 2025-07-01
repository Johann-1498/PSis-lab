#pragma once

/// Tipos de operación que se pueden registrar.
enum class TipoOperacion {
    RETIRO,    // Desde una bóveda hacia el transportador
    DEPOSITO,  // Desde el transportador hacia una bóveda
    INICIAL,   // Depósito inicial en una bóveda (sin transportador/origen externo)
    TRASLADO   // (Mantenido del código original, aunque el flujo lo descompone en DEPOSITO/RETIRO)
};